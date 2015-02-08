/*
 * UDPSock.h
 *
 *  Created on: Feb 8, 2015
 *      Author: robert
 */

#ifndef UDPSOCK_H_
#define UDPSOCK_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

struct hostent *gethostbyname() ;
void printSA(struct sockaddr_in sa) ;
void makeDestSA(struct sockaddr_in * sa, char *hostname, int port) ;
void makeLocalSA(struct sockaddr_in *sa) ;
void receiver(int port) ;
void sender(char *message1, char *message2,char *machine, int port);

#define RECIPIENT_PORT 1234
#define SIZE 1000

#endif /* UDPSOCK_H_ */
