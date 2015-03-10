Created by Robert Clabough

Remote Procedure Call.

Goal: To build a custom remote procedure call client and server for linux.  A client must be able to connect to an active server and receive messages back.  A server must be able to run continuously and handle multiple client interactions.  In this case, the simple arithmetic operations are supported, as mentioned below.
  
How to use and compile:

First, all of the values are set in src/constants.h.  This is where IP addresses and ports are set for both the client
the server.  Each client and server can have their own constant.h.  For example, the server can have their own IP and port
specified, and the client doesn't matter.  For each client, all four fields must be filled out correctly to work.

When sending a message, a client will create a comma delimited string.  By doing this, there is a standard across all 
platform by using ASCII.  The values follow this form:

  RETURN_ADDRESS,RETURN_PORT,RPCID,RPC_METHOD,ARG1,ARG2,REQUEST/REPLY
  
  RETURN_ADDRESS: (String)
      The client's IP address, the server will use this value to know where to send the response
      message back to the client.
  
  RETURN_PORT:  (Integer)
      The client's port that is open to the response
      
  RPCID:  (Integer)
      Unique identifier of the current procedure call
      
  RPC_Method: (Integer)
      Specifies which method to call on the remote server.
      
  ARG1: (Integer)
      First argument, or return value on replies
      
  ARG2: (Integer)
      Second argument
      
  REQUEST/REPLY: (Integer)
      0 for request, 1 for reply
  
Part 1:
  Echo user input
  
  I built the echo function into Echo.out/c.  It takes in only INTEGER input, as adding a char* for the meantime broke my arithmitic from part 2.  The use is as follows:
    Echo.out 77
    
  Echo will then return 77 from the server.  To run the server, it is the same as in part 2.  I've built in a function to make to allow this to run.  Once again, the server and client inputs are based off of constants.h, which is where the IP address / name are stored.  To run the server, use the command:
    make runRPCServer
    
  This will start the server running on the specfied port from constants.h

  Then, to run Echo, simply run 'make Echo', or make in general, and run:
  	Echo.out #
	Where # is the number you would like to echo.

Part 2:
  Client receiver.

  For this, the server is exactly the same, and the make command make runRPCServer will still work.  Once again, make sure all of the constants are up to date in constants.h.  The
  server was giving a segfault sometimes while running on pyrite when I wasn't using the exact IP address of the machine.  On VM's and non-cluster computers this didn't seem to be
  a problem, but on pyrite and popeye this did cause issues, even with localhost sometimes.

  To run the client, all that is needed is to once again call 
  	make runRPCClient
  This will start the client and allow bring them to a menu.  From the menu, there are a bunch of options for which arithmatic service is allowed.  Please note that since
  this is an implementation of DoOperation, it will hang if no response is provided.

If there are any questions with my code, or have issues compiling, please feel free to contact me at rmcn96@iastate.edu

Thank you for taking the time to read this README, hopefully it will be helpful in using my code.
