/*
 ============================================================================
 Name        : ComS454Proj1.c
 Author      : Robert Clabough
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "UDPSock.h"
#include "rpc.h"
#include "receiver.h"


void SendTest();

/* main for sender and receiver - to send give s machine messag1 and message2
	- to receive give r
	*/


void main(int argc,char **argv)
{
	int port = 1234;

	if(argc <= 1){
		printf("Usage:s(end) ...or r(eceive) ??\n");
		exit(1);
	}
	if(*argv[1]  == 's'){/**
		if(argc <=2) {
			printf("Usage: s  machine message1 message2\n");
			exit(1);
		}
		sender(argv[3], argv[4], argv[2],port);**/
		SendTest();
	}else if(*argv[1]  == 'r') {
		responderRunner();
		}
	else printf("send machine or receive??\n");
}


void SendTest()
{

	Message message;
	unsigned char myString [1000] = "This is my string";

	message.data = "1234,localhost,This is my string,This is my response.";
	message.length = strlen(message.data);
	/**message->data = (unsigned char*)malloc(sizeof(unsigned char) * message->length);**/
	Message *reply = malloc(sizeof(Message));
	int s = 0; /** Don't know what this is... **/
	SocketAddress server;
	char* host = "localhost";
	int port = IPPORT_RESERVED + 0230;
	makeDestSA(&server, host, port);
	DoOperation (&message, reply, s, server);
}
