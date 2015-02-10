#include "rpc.h"




Status DoOperation(Message *message, Message *reply, int s,
		SocketAddress serverSA) {

	printf("DoOperation\n");
	printf("Send outbound message...\n");
	UDPsend(s, message, serverSA);
	UDPreceive(s, reply, &serverSA, 1234);
	printf("Response: %s\n", reply->data);
}

Status  UDPsend(int s, Message *m, SocketAddress destination){
/**Create local address **/
	char* msg;
	int n;
	struct sockaddr_in mySocketAddress;

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
/**
	printf("My address:\n");
	printSA(mySocketAddress);
	printf("Server Address:\n");
	printSA(destination);
	printf("Data: %s\t%d\n", m->data, m->length);
	**/
		if( (n = sendto(s, m->data, m->length, 0, (struct sockaddr *)&destination,
			sizeof(struct sockaddr_in))) < 0)
			perror("Send failed\n");
		/**
		if(n != strlen(m)) printf("sent %d\n",n);**/
		return OK;
}


Status  UDPreceive(int s, Message *m, SocketAddress *origin, int port)
{

	char message1[SIZE], message2[SIZE];
	struct sockaddr_in mySocketAddress, aSocketAddress;
	int aLength, n;
	int i;

	if((s = socket(AF_INET, SOCK_DGRAM, 0))<0) {
		perror("socket failed");
		return BAD;
	}
	makeReceiverSA(&mySocketAddress, port);

	if( bind(s, (struct sockaddr *)&mySocketAddress, sizeof(struct sockaddr_in))!= 0){
		perror("Bind failed\n");
		close(s);
		return BAD;
	}
/**
	printSA(mySocketAddress);**/
	aLength = sizeof(aSocketAddress);
	aSocketAddress.sin_family = AF_INET;


	if((n = recvfrom(s, message1,  SIZE, 0, (struct sockaddr *)&aSocketAddress, &aLength))<0)
		perror("Receive 1") ;
	else{
		/**
		printSA(aSocketAddress);
		for(i=0; i<n; i++) printf("M:%d", message1[i]);

		printf("\n Received Message:(%s)length = %d \n",
			message1,n);**/
		//strcpy(message1, m->data);
		m->data = message1;
		m->length = n;
	}
	origin = &aSocketAddress;
	close(s);
	return OK;
}

/**
 * This method was created by 'hmjd' on StackOverflow.  The original code can be found at
 * http://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
 */
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

