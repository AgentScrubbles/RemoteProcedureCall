rpc:	RPC HelloWorld

dir:
	mkdir obj bin

HelloWorld: Main
	gcc -o bin/a.out -lc obj/ComS454Proj1.o obj/rpc.o obj/UDPSock.o
	
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
