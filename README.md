Created by Robert Clabough

Computer Science 454

Project 1

This project follows the specifications of the project 1 found at 
  http://www.cs.iastate.edu/~cs554/RPCproject.htm
  
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
  
