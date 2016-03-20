/*
 * Code source du programme netscan
 *
 * Utilitaire de scan des ports ouverts
 * sur une IP.
 *
 * Version : 1.0
 *
 * Fichier ... functions.h
 * Utilité ... Code d'en-têtes de fonctions
 * Date ...... 14/05/2013
 * Auteur .... Théophile Walter
 * 
 * Fonctions : isValidIp4();
 *             TCPCheckPort();
 *
 * Dépendences : ws2_32.lib
 *
 * © Copyright 2013 Théophile Walter
 *
 */


#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


// Déclaration des fonctions...
int  isValidIp4       ( char * str );
int  TCPCheckPort     ( char * IP  , int PORT );
int  ScanPorts        ( void       );


#endif

