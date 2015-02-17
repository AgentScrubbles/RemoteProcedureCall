/**
 * Crated by Robert Clabough
 *
 * Echos client input to the server defined in constants.h to the client.
 *
 * Use is Echo "String"
 *
 * Where the first argument is the string that is requested to be echoed.
 *
 *
 * **/

#include "constants.h"
#include "rpc.h"

void main(int argc, char **argv){
	if(argc <= 1){
		printf("Error, please enter a string to echo\n");
		exit(1);
	}

	char* arg = argv[1];

	printf("Will be echoing: %s\n", arg);

	RPCMessage rpc;

	rpc.machine = CLIENT_ADDR;
	rpc.port = CLIENT_PORT;
	char* remoteServerAddr = SERVER_ADDR;
	int remoteServerPort = SERVER_PORT;

	rpc.procedureId = 6; /** ECHO COMMAND **/
	/**rpc.strArg = argv[1];**/
	memset(rpc.strArg, '\0', sizeof(char)* 100);
	strcpy(rpc.strArg, argv[1]);
	printf("%s\n", rpc.strArg);
	rpc.RPCId = 0;
	rpc.messageType = Request;
	Message msg;
	Message reply;
	int s = 0;
	marshal(&rpc, &msg);
	SocketAddress server;
	makeDestSA(&server, remoteServerAddr, remoteServerPort);
	DoOperation(&msg, &reply, s, server);

}