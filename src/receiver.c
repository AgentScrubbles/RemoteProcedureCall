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
	makeReceiverSA(&mySocketAddress, RECEIVER_PORT);
	int s = 0;
	while(1)
	{
		Message* msg = malloc(sizeof(Message));
		Status s = UDPreceive(s, msg, mySocketAddress);

		clone(receive, void *child_stack, int flags, msg);
	}
}
