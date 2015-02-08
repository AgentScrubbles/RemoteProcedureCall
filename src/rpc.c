
#include "rpc.h"

Status DoOperation (Message *message, Message *reply, int s, SocketAddress serverSA)
{
	/**Create local address **/
	SocketAddress mySA;
	makeLocalSA(&mySA);
	printf("DoOperation\n");
}
