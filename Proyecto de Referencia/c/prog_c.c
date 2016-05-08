#include "comm.h"
#include <string.h> // strncpy
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    char buffer[10];
    mqd_t cola;
    struct mq_attr attr = {
        .mq_flags = 0,    /* Message queue flags.  */
        .mq_maxmsg = 10,   /* Maximum number of messages.  */
        .mq_msgsize = 10,  /* Maximum message size.  */
        .mq_curmsgs = 0,  /* Number of messages currently queued.  */
    };
    cola = mq_open("/mq_a",
        O_CREAT | O_RDWR, 0600, &attr);
    if (cola < 0) {
        perror("mq_open");
        return -1;
    }

    printf("La cola devolvio: %d", cola);
    TMensaje m;
    int count = 10;


    srand(getpid());

    iniciar(argc, argv, &m);

    strcpy(m.imagen, "pelota.png");

    m.x = rand() % 800;
    m.y = rand() % 540;
    printf("%d %d\n", m.x, m.y);
    m.x += 1;
    m.y = 1;
    m.pid = getpid();
    enviar(&m);
    mq_receive(cola, (char *) &buffer, attr.mq_msgsize, 0);
    printf("No debería seguir!");
    while(count-- > 0)
    {
        // Enviar el mensaje
        m.x += 1;
        m.y = 1;
        m.pid = getpid();
        enviar(&m);
        usleep(500000);
        if ( count == 5) {
            strcpy(m.imagen, "pantera.png");
        }
    }

    return 0;
}
