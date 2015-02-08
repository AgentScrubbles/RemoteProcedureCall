#include "rpc.h"



Status DoOperation(Message *message, Message *reply, int s,
		SocketAddress serverSA) {

	printf("DoOperation\n");
	printf("Send outbound message...\n");
	UDPsend(s, message, serverSA);
	UDPreceive(s, reply, serverSA);
}

Status  UDPsend(int s, Message *m, SocketAddress destination){
/**Create local address **/
	char* msg;
	int n;
	struct sockaddr_in mySocketAddress, yourSocketAddress;

	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket failed");
		return BAD;
	}

	makeLocalSA(&mySocketAddress);

	if (bind(s, (struct sockaddr *) &mySocketAddress,
			sizeof(struct sockaddr_in)) != 0) {
		perror("Bind failed\n");
		close(s);
		return BAD;
	}

	printf("My address:\n");
	printSA(mySocketAddress);
	printf("Server Address:\n");
	printSA(destination);

	strcpy(msg,m->data);
		if( (n = sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&yourSocketAddress,
			sizeof(struct sockaddr_in))) < 0)
			perror("Send failed\n");
		if(n != strlen(m)) printf("sent %d\n",n);
		return OK;
}


Status  UDPreceive(int s, Message *m, SocketAddress *origin)
{

}
