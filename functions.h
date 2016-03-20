/*
 * Code source du programme netscan
 *
 * Utilitaire de scan des ports ouverts
 * sur une IP.
 *
 * Version : 1.0
 *
 * Fichier ... functions.h
 * Utilit� ... Code d'en-t�tes de fonctions
 * Date ...... 14/05/2013
 * Auteur .... Th�ophile Walter
 * 
 * Fonctions : isValidIp4();
 *             TCPCheckPort();
 *
 * D�pendences : ws2_32.lib
 *
 * � Copyright 2013 Th�ophile Walter
 *
 */


#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


// D�claration des fonctions...
int  isValidIp4       ( char * str );
int  TCPCheckPort     ( char * IP  , int PORT );
int  ScanPorts        ( void       );


#endif

