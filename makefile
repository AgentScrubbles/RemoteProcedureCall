proj1: HelloWorld

HelloWorld: Main
	gcc -o bin/a.out -lc obj/ComS454Proj1.o
	
SocketTest: UDPSock
	gcc -o bin/socket.out -lc obj/UDPSock.c

Main:
	gcc -o obj/ComS454Proj1.o -c src/ComS454Proj1.c

UDPSock:
	gcc -o obj/UDPSock.o -c src/UDPSock.c
