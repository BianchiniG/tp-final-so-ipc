#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <stdlib.h>
#include "prod_cons.h"

int main(void)
{
	mqd_t mqd;
	char c;
	prodcons_msg msg;
	int count;
	struct mq_attr mqa;

	/*
         struct mq_attr {
             long mq_flags;       // Flags: 0 or O_NONBLOCK
             long mq_maxmsg;      // Max. # of messages on queue
             long mq_msgsize;     // Max. message size (bytes)
             long mq_curmsgs;     // # of messages currently in queue
         };
	*/
	mqa.mq_flags = 0;       // Flags: 0 or O_NONBLOCK
	mqa.mq_maxmsg = 512;      // Max. # of messages on queue
	mqa.mq_msgsize = sizeof(prodcons_msg);     // Max. message size (bytes)
	mqa.mq_curmsgs = 0;     // # of messages currently in queue

	mqd = mq_open("/first_mq", O_RDWR | O_CREAT, 0700, &mqa);
	if(mqd == (mqd_t) -1)
	{
		perror("mq_open");
		exit(1);
	}

	count = 0;
	while(read(0, &c, 1))
	{
		msg.c = c;
		msg.i = count++;
		mq_send(mqd, (const char *) &msg, sizeof(prodcons_msg), 1);
	}
}

