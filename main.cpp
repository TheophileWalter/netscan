/*
 * Code source du programme netscan
 *
 * Utilitaire de scan des ports ouverts
 * sur une IP.
 *
 * Version : 1.0
 *
 * Fichier ... main.cpp
 * Utilit� ... Code principal du programme
 * Date ...... 14/05/2013
 * Auteur .... Th�ophile Walter
 * 
 * Fonctions : main()
 *             ScanPorts()
 *
 * D�pendences : ws2_32.lib
 *
 * � Copyright 2013 Th�ophile Walter
 *
 */

#include <iostream>
#include <Winsock2.h>
#include <Windows.h>
#include "functions.h"
#include "main.h"
using namespace std;

int StartPort, EndPort;
char * IPToScan;
bool PortScanned[65536];

int main ( int argc, char * argv [] )
{
	// V�rifis le nombre de param�tres...
	if (argc<=3)
	{
		// Affiche une erreur...
		cout << "Erreur : Utilisez les param�tres suivants :" << endl << "	ip start end : Scan tous les ports ouverts sur l'IP entre \"start\" et \"end\"." << endl << "		Exemple : \"netscan 127.0.0.1 0 65535\" scan tous les ports de l'ordinateur." << endl << endl;

		// Retourne une erreur...
		return 1;
	}

	// V�rifis si l'adesse IP n'est pas valide...
	IPToScan = argv[1];
	if (! isValidIp4(IPToScan))
	{
		// Affiche une erreur ...
		cout << "Erreur : Le premier param�tres doit �tre une adresse IP au format IPv4 !" << endl << endl;

		// Retourne une erreur...
		return 1;
	}

	// V�rifis lse ports...
	StartPort = atoi ( argv[2]);
	EndPort = atoi (argv[3]);
	if (StartPort < 0 || StartPort > 65535 || EndPort < 0 || EndPort > 65535 || StartPort > EndPort)
	{
		// Affiche une erreur ...
		cout << "Erreur : Un port doit �tre compris entre 0 et 65535 (inclus) et le port de d�part doit �tre inf�rieur � celui d'arriv� !" << endl << endl;

		// Retourne une erreur...
		return 1;
	}

	// Scan les ports...
	// Cr�e des thread de scan...
	DWORD ThreadId;
	HANDLE ThreadHandles[MAX_THREAD];
	for (int i = 0; i < MAX_THREAD; i++)
		ThreadHandles[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ScanPorts, NULL, 0, &ThreadId);

	// Attend que tous les Thread soient termin�s...
	while (true)
	{
		bool Exit = true;
		for (int i = 0; i < MAX_THREAD; i++)
		{
			DWORD  ReturnLP;
			GetExitCodeThread(ThreadHandles[i], &ReturnLP);
			if (ReturnLP == STILL_ACTIVE)
				Exit = false;
		}
		if (Exit)
			return 0;
		Sleep ( 100);
	}
}

int ScanPorts ( void )
{
	for (int i = StartPort; i <= EndPort; i++)
	{
		// V�rifis si le port n'a pas �t� scann� par un autre Thread...
		if (! PortScanned[i])
		{
			// Enregistre le port comme scann�...
			PortScanned[i] = true;

			if (TCPCheckPort(IPToScan, i) == 1)
				cout << i << endl;
		}
	}
	return 1;
}