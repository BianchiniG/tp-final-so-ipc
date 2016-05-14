#include "comun.h"

char buffer[MAX_BUFFER];
int atendiendose = 0;

void sig(int s) {
    atendiendose = 1;
}

int main() {

    // Define las variables para las colas de mensajes del barbero y clientes
    mqd_t cola;

    signal(SIGUSR1, sig);

    // Crea la cola.
    cola = mq_open(COLA_C, O_CREAT | O_RDWR, 0600, &atrib);

    while(1) {
        int estado, stat_env;

        if (fork()){
            // waitpid(0, &estado, 0);
        } else {
            m.pid = getpid();

            printf(ANSI_COLOR_YELLOW
                    "Cliente %d: Llegue!"
                    ANSI_COLOR_RESET
                    "\n",
                    getpid());

            stat_env = mq_send(cola, (const char *) &m, sizeof(mensaje), 0);

            // Espera a ser atendido.
            while(!atendiendose)
                ;
                
            atendiendose = 0;

            printf(ANSI_COLOR_YELLOW
                "Cliente %d: Me atendió!"
                ANSI_COLOR_RESET
                "\n",
                getpid());
        }

        sleep(1);
    }

    return 0;
}

/* Error de cola llena
RETURN VALUE
       On success, mq_send() and mq_timedsend() return zero; on error, -1 is
       returned, with errno set to indicate the error.

ERRORS
       EAGAIN The queue was full, and the O_NONBLOCK flag was set for the
       message queue description referred to by mqdes.
*/
