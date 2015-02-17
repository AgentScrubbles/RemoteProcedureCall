/*
 * receiver.c
 *
 *  Created on: Feb 9, 2015
 *      Author: robert
 */

#include "receiver.h"

Status responderRunner(int port)
{
	int s = 0;
	int tid = 0;
	printf("Server is running on port %d...\n", port);
	while(1)
	{
		printf("Listening...\n");
		ClientMessage* rpc_msg = (ClientMessage*)malloc(sizeof(ClientMessage));
		Status s = UDPreceive(s, &rpc_msg->msg, &rpc_msg->client, port);
		if(s == BAD) return BAD;
		void* child_stack=(void*)malloc(16384);
		child_stack+=16383;
		rpc_msg->stack = child_stack; /** keep a pointer to the stack **/
		tid = clone(receive, child_stack, CLONE_VM, rpc_msg);
		printf("Message thread started on thread ID %d\n", tid);
	}
	return OK;
}

Status receive(ClientMessage* msg){
	ClientMessage* message = msg;
	printf("\n\n**Message Received**\n\t%s\n", message->msg.data);
	unMarshal(&message->rpc, &message->msg);
	printf("Return address: %s\nReturn port: %d\n", message->rpc.machine, message->rpc.port);

	

	int ret = rpcMethod(message->rpc.arg1, message->rpc.arg2, message->rpc.procedureId);

	printf("\t%d (%d) %d = %d\n", message->rpc.arg1, message->rpc.procedureId, message->rpc.arg2, ret);

	printf("**Making response***\n");
	 /** Simulating a slow response **/
	 sleep(1);
	
	struct sockaddr_in destination;
	makeDestSA(&destination, message->rpc.machine, message->rpc.port);
	printf("Socket created.\n");
	int s = 0;
	RPCMessage responseMessage;
	Message responseMsg;
	responseMessage.RPCId = message->rpc.RPCId;
	responseMessage.arg1 = ret;
	responseMessage.arg2 = 0;
	responseMessage.machine = SERVER_ADDR; /** Assume client knows the response **/
	responseMessage.port = SERVER_PORT; /**Asume client knows the response port **/
	responseMessage.procedureId = 0; /**Meaningless on the response **/
	responseMessage.messageType = Reply;
	marshal(&responseMessage, &responseMsg);
	UDPsend(s, &responseMsg, destination);
	printf("Response Message:\n\t%s\n", responseMsg.data);
	printf("********************\n\n");
	/**free(message->stack); ** Free the current stack space, may freak out **/
	free(message);
	return OK;
}

int rpcMethod(int arg1, int arg2, int procedureID){
	switch(procedureID){
	case 0:
		return arg1 + arg2;
		break;
	case 1:
		return arg1 - arg2;
		break;
	case 2:
		return arg1 * arg2;
		break;
	case 3:
		return arg1 / arg2;
		break;
	case 4:
		/** PING **/
		break;
	case 5:
		/** STOP **/
		printf("Server stopping...\n\n");
		exit(0);
		break;
	default:
		return arg1 + arg2;
		break;
	}
	return 0;
}
