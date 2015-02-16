/*
 * RPCServer.c
 *
 *  Created on: Feb 13, 2015
 *      Author: robert
 */

#include "receiver.h"


void main(int argc,char **argv)
{
	/**
	if(argc <= 1){
		printf("Use:\nRPCServer [Server Port]");
		return;
	}
	int port = atoi(argv[1]);
	**/
	int port = SERVER_PORT;
	responderRunner(port);

}
