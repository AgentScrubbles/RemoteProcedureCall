/*
 * receiver.c
 *
 *  Created on: Feb 9, 2015
 *      Author: robert
 */

#include "receiver.h"

Status responderRunner()
{
	int s = 0;

	while(1)
	{
		RPCMessage rpc_msg;
		Status s = UDPreceive(s, &rpc_msg.msg, &rpc_msg.client, RECEIVER_PORT);
		if(s == BAD) return BAD;
		RPCMessage rpc;
		void* child_stack=(void*)malloc(16384);
		child_stack+=16383;
		clone(receive, child_stack, CLONE_VM, (void*)&rpc_msg);
	}
	return OK;
}

Status receive(void* msg){
	RPCMessage* message = (RPCMessage*)msg;
	printf("In receive thread, the message is : %s\n", message->msg.data);

	char** items = str_split(message->msg.data, ',');
	if (items)
	    {
	        int i;
	        for (i = 0; *(items + i); i++)
	        {
	            printf("month=[%s]\n", *(items + i));
	        }
	        printf("\n");
	    }
	message->callbackPort = atoi(items[0]);
	message->callbackAddr = items[1];
	SocketAddress returnAddress;
	makeDestSA(&returnAddress, message->callbackAddr, message->callbackPort);
	message->response.data = items[3];
	message->response.length = strlen(message->response.data);
	UDPsend(0, &message->response, returnAddress);
	printf("Send complete.\n");
	return OK;
}
