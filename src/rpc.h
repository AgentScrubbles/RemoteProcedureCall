/*
 * rpc.h
 *
 *  Created on: Feb 8, 2015
 *      Author: robert
 */

#ifndef RPC_H_
#define RPC_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <assert.h>

#include "UDPSock.h"


#define SIZE 1000
#define RECEIVER_PORT IPPORT_RESERVED + 0230


typedef struct {
	unsigned int length;
	unsigned char* data;
} Message;
typedef enum {
	OK, /* operation successful */
	BAD, /* unrecoverable error */
	WRONGLENGTH /* bad message length supplied */
} Status;
typedef struct sockaddr_in SocketAddress;
typedef struct{ /**Used in the receiver to keep data together **/
	Message msg;
	Message response;
	SocketAddress client;
	int callbackPort;
	char* callbackAddr;
}RPCMessage;

Status DoOperation (Message *message, Message *reply, int s, SocketAddress serverSA);
Status GetRequest (Message *callMessage, int s, SocketAddress *clientSA);
Status SendReply (Message *replyMessage, int s, SocketAddress clientSA);

Status  UDPsend(int s, Message *m, SocketAddress destination);
Status  UDPreceive(int s, Message *m, SocketAddress *origin, int port);


char** str_split(char* a_str, const char a_delim);
#endif /* RPC_H_ */
