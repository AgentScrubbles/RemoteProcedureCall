rpc:	RPC HelloWorld

runReceiver: receiver
	bin/receiver.out r

runSender: Sender
	bin/sender.out s

receiver: Receiver RPC UDPSock Main
	gcc -o bin/receiver.out -lc obj/ComS454Proj1.o obj/UDPSock.o obj/rpc.o obj/receiver.o

Receiver: RPC
	gcc -w -o obj/receiver.o -c src/receiver.c

dir:
	mkdir obj bin

Sender: Main Receiver RPC UDPSock
	gcc -o bin/sender.out -lc obj/ComS454Proj1.o obj/rpc.o obj/UDPSock.o obj/receiver.o
	
SocketTest: UDPSock
	gcc -o bin/socket.out -lc obj/UDPSock.o
	cp bin/socket.out bin/socketRec.out

Main:
	gcc -w -o obj/ComS454Proj1.o -c src/ComS454Proj1.c

UDPSock:
	gcc -w -o obj/UDPSock.o -c src/UDPSock.c
	
RPC: UDPSock
	gcc -w -o obj/rpc.o -c src/rpc.c
	
cleanup:
	clear
	rm obj/*
	rm bin/*
