#include "comm.h"
#include <string.h> // strncpy
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    sem_t *sem;

    sem = sem_open("/sem_a", O_CREAT, 0600, 0);
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
    sem_wait(sem);
    
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
