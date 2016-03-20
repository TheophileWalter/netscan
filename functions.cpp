/*
 * Code source du programme netscan
 *
 * Utilitaire de scan des ports ouverts
 * sur une IP.
 *
 * Version : 1.0
 *
 * Fichier ... functions.cpp
 * Utilité ... Code de fonctions
 * Date ...... 14/05/2013
 * Auteur .... Théophile Walter
 * 
 * Fonctions : isValidIp4()
 *             TCPCheckPort()
 *
 * Dépendences : ws2_32.lib
 *
 * © Copyright 2013 Théophile Walter
 *
 */

#include <iostream>
#include <Winsock2.h>
#include <Windows.h>
#include "functions.h"
#include "main.h"
using namespace std;

int isValidIp4 (char *str) {
	int segs = 0;   /* Segment count. */
	int chcnt = 0;  /* Character count within segment. */
	int accum = 0;  /* Accumulator for segment. */

	/* Catch NULL pointer. */

	if (str == NULL)
		return 0;

	/* Process every character in string. */

	while (*str != '\0') {
		/* Segment changeover. */

		if (*str == '.') {
			/* Must have some digits in segment. */

			if (chcnt == 0)
				return 0;

			/* Limit number of segments. */

			if (++segs == 4)
				return 0;

			/* Reset segment values and restart loop. */

			chcnt = accum = 0;
			str++;
			continue;
		}

 

		/* Check numeric. */

		if ((*str < '0') || (*str > '9'))
			return 0;

		/* Accumulate and check segment. */

		if ((accum = accum * 10 + *str - '0') > 255)
			return 0;

		/* Advance other segment specific stuff and continue loop. */

		chcnt++;
		str++;
	}

	/* Check enough segments and enough characters in last segment. */

	if (segs != 3)
		return 0;

	if (chcnt == 0)
		return 0;

	/* Address okay. */

	 return 1;
}

// Vérifis si un port est ouvert...
int TCPCheckPort ( char * IP, int PORT)
{
	// Initialisation du protocol TCP/IP...
	WSADATA wsa;
	int error = WSAStartup(MAKEWORD(2, 2), &wsa);
	if(error < 0)
		return 0;
	
	// Création du socket...
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
		return 0;
	
	// Création d'une interface d'envoi...
	SOCKADDR_IN sin = { 0 };
	sin.sin_addr.s_addr = inet_addr(IP);// Adresse de serveur.
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);// Port du serveur.
	if(connect (sock,(struct sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR)
		return 0;

	// Fermeture du socket serveur...
	closesocket(sock);

	// Fin du protocol TCP/IP...
	WSACleanup();

	return 1;
}