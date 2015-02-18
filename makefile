rpc:	ClientServer Echo


ClientServer: RPCClient RPCServer


Echo: RPC
	gcc -o obj/Echo.o -c src/Echo.c
	gcc -o bin/Echo.out -lc obj/Echo.o obj/rpc.o obj/UDPSock.o

runRPCClient: RPCClient
	bin/RPCClient.out
	
runRPCServer: RPCServer
	bin/RPCServer.out

RPCServer: RPC Receiver
	gcc -o obj/RPCServer.o -c src/RPCServer.c
	gcc -o bin/RPCServer.out -lc obj/RPCServer.o obj/rpc.o obj/UDPSock.o  obj/receiver.o

RPCClient: RPC
	gcc -o obj/RPCClient.o -c src/RPCClient.c
	gcc -o bin/RPCClient.out -lc obj/RPCClient.o obj/rpc.o obj/UDPSock.o

Receiver: RPC
	gcc -w -o obj/receiver.o -c src/receiver.c

dir:
	mkdir obj bin

Sender: Main Receiver RPC UDPSock
	gcc -o bin/sender.out -lc obj/ComS454Proj1.o obj/rpc.o obj/UDPSock.o obj/receiver.o
	


UDPSock:
	gcc -w -o obj/UDPSock.o -c src/UDPSock.c
	
RPC: UDPSock
	gcc -w -o obj/rpc.o -c src/rpc.c
	
cleanup:
	clear
	rm obj/*
	rm bin/*
