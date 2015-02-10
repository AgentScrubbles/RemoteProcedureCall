/*
 * receiver.c
 *
 *  Created on: Feb 9, 2015
 *      Author: robert
 */

#include "receiver.h"

Status responderRunner()
{
	SocketAddress mySocketAddress;
	int s = 0;

	while(1)
	{
		Message* msg = malloc(sizeof(Message));
		Status s = UDPreceive(s, msg, &mySocketAddress);
		if(s == BAD) return BAD;
		void* child_stack=(void*)malloc(16384);
		child_stack+=16383;
		clone(receive, child_stack, CLONE_VM, msg);
	}
	return OK;
}

Status receive(Message* msg){
	printf("In receive, new thread created\n");
	return OK;
}
