/**
 * Receiver is a file that will run as the server code.  It will receive messages, then create a thread that will process and respond
 * to the request.
 */
#include <sched.h>
#include "rpc.h"


Status responderRunner();

Status receive(SocketAddress repond, Message* msg);


