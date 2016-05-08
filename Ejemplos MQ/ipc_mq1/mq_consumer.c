#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <errno.h>
#include "prod_cons.h"

int main(void)
{
	mqd_t mqd;
//	char c;
	prodcons_msg msg;
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

	mq_getattr(mqd, &mqa);
	printf("mq_attr.mq_flags = %ld\n", mqa.mq_flags);
	printf("mq_attr.mq_maxmsg = %ld\n", mqa.mq_maxmsg);
	printf("mq_attr.mq_msgsize = %ld\n", mqa.mq_msgsize);
	printf("mq_attr.mq_curmsgs = %ld\n", mqa.mq_curmsgs);

	while(1)
	{
		if(mq_receive(mqd, (char *) &msg, sizeof(prodcons_msg), NULL) == -1)
		{
			perror("mq_receive");
			exit(1);
		}
		write(1, &(msg.c), 1);
//		printf("msg.i = (%d)\n", msg.i);
		printf("%d", msg.i);
		fflush(stdout);
	}
}

