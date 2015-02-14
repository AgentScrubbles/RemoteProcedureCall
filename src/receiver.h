/**
 * Receiver is a file that will run as the server code.  It will receive messages, then create a thread that will process and respond
 * to the request.
 */
#include <sched.h>
#include "rpc.h"
#define _GNU_SOURCE
#include <linux/sched.h>


Status responderRunner(int port);

Status receive(void* msg);


