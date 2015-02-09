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

	char message1[SIZE], message2[SIZE];
	struct sockaddr_in mySocketAddress, aSocketAddress;
	int aLength, n;
	int i;

	if((s = socket(AF_INET, SOCK_DGRAM, 0))<0) {
		perror("socket failed");
		return BAD;
	}
	makeReceiverSA(&mySocketAddress, RECIPIENT_PORT);

	if( bind(s, (struct sockaddr *)&mySocketAddress, sizeof(struct sockaddr_in))!= 0){
		perror("Bind failed\n");
		close(s);
		return BAD;
	}

	printSA(mySocketAddress);
	aLength = sizeof(aSocketAddress);
	aSocketAddress.sin_family = AF_INET;


	if((n = recvfrom(s, message1,  SIZE, 0, (struct sockaddr *)&aSocketAddress, &aLength))<0)
		perror("Receive 1") ;
	else{
		printSA(aSocketAddress);
		for(i=0; i<n; i++) printf("M:%d", message1[i]);
		printf("\n Received Message:(%s)length = %d \n",
			message1,n);
		strcpy(message1, m->data);
		m->length = n;
	}
	close(s);
	return OK;
}
