#include "comm.h"
#include <string.h> // strncpy
#include <unistd.h>


int main(int argc, char **argv)
{
    char buffer[10] = "Mensaje";
    mqd_t cola;
    struct mq_attr attr = {
        .mq_flags = 0,    /* Message queue flags.  */
        .mq_maxmsg = 10,   /* Maximum number of messages.  */
        .mq_msgsize = 10,  /* Maximum message size.  */
        .mq_curmsgs = 0,  /* Number of messages currently queued.  */
    };
    TMensaje m;
    int count = 10;
    cola = mq_open("/mq_a",
        O_CREAT | O_RDWR, 0600, &attr);
    if (cola < 0) {
        perror("mq_open");
        return -1;
    }

    iniciar(argc, argv, &m);
    mq_send(cola, (char *)&buffer, sizeof(buffer), 0);
    while(count-- > 0)
    {
        // Enviar el mensaje
        m.x = count;
        m.y = count +1;
        m.pid = getpid();
        enviar(&m);
        usleep(500000);
    }
    // Avisa a Processing que se va
    m.estado = -1;
    enviar(&m);

    return 0;
}
