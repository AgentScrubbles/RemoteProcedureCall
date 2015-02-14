/*
 * RPCClient.c
 *
 *  Created on: Feb 13, 2015
 *      Author: robert
 */
#include "rpc.h"
#include "UDPSock.h"

/**
 * Usage, RPCClient machine port
 * **/
void main(int argc, char **argv) {
	char* remoteServerAddr;
	int remoteServerPort;
	RPCMessage rpc;
	if (argc <= 1) {
		rpc.machine = malloc(100);
		remoteServerAddr = malloc(100);
		printf("\n");
		scanf("Please enter the local address: %s", rpc.machine);
		scanf("Please enter the local port: %d", &rpc.port);
		scanf("Please enter the server address: %s", remoteServerAddr);
		scanf("Please enter the server port: %d", &remoteServerPort);
		printf(
				"Settings:\n\tLocal:\n\tMachine: %s\n\tPort: %d\n\n\tServer:\n\tMachine: %s\n\tPort: %d\n\n",
				rpc.machine, rpc.port, remoteServerAddr, remoteServerPort);
		return;
	} else {
		remoteServerPort = atoi(argv[1]);
		remoteServerAddr = argv[2];
		rpc.port = atoi(argv[3]);
		rpc.machine = argv[4];
	}

	rpc.procedureId = 0;
	while (rpc.procedureId != 9) {
		printf("\n\n\n-----------------------------\n");
		printf("Enter the info for the query.\n");
		printf("In the form of [operation] [arg1] [arg2]\n");
		printf("Operation options:\n");
		printf("\t0:\tAdd      (+)\n");
		printf("\t1:\tSubtract (-)\n");
		printf("\t2:\tMultiply (*)\n");
		printf("\t3:\tDivision (/)\n");
		printf("\t4:\tPing Server\n");
		printf("\t5:\tStop Server\n");
		printf("\t9:\tQuit\n\n");
		scanf("%d %d %d", &rpc.procedureId, &rpc.arg1, &rpc.arg2);
		printf("\t%d (%d) %d = ?\n", rpc.arg1, rpc.procedureId, rpc.arg2);
		if(rpc.procedureId == 9) return;
		rpc.RPCId = 0;
		rpc.messageType = Request;
		Message msg; /** Initialized internally by marshall **/
		Message reply;
		int s = 0;
		marshal(&rpc, &msg);
		SocketAddress server;
		makeDestSA(&server, remoteServerAddr, remoteServerPort);
		DoOperation(&msg, &reply, s, server, rpc.port);
	}
}

