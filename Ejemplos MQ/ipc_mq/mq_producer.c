/* mq_producer.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

int main(void)
{
	mqd_t mqd;
	char c;
	struct mq_attr mqa;

	mqa.mq_flags = 0;       // Flags: 0 or O_NONBLOCK
	mqa.mq_maxmsg = 512;      // Max. # of messages on queue
	mqa.mq_msgsize = 1;     // Max. message size (bytes)
	mqa.mq_curmsgs = 0;     // # of messages currently in queue

	mqd = mq_open("/fir_mq", O_RDWR | O_CREAT, 0700, &mqa);

	if(mqd == (mqd_t) -1)
	{
		perror("mq_open");
		exit(1);
	}

	while(read(0, &c, 1))
		mq_send(mqd, &c, 1, 0);
}
