#include "comun.h"

int main() {

    // Define las variables para las colas de mensajes del barbero y clientes
    mqd_t cola_c;
    mqd_t cola_p;
    // mqd_t cola_count;
    // mqd_t cola_prior;
    char buffer[MAX_BUFFER];

    // Crea las colas.
    cola_c = mq_open(COLA_C, O_CREAT | O_RDWR, 0600, &atrib_c);
    cola_p = mq_open(COLA_P, O_CREAT | O_RDWR, 0600, &atrib_b);

    while(1) {
        int estado, stat_env;

        if (fork()){
            // waitpid(0, &estado, 0);
        } else {
            m_c.pid = getpid();

            printf(ANSI_COLOR_YELLOW
                    "*** Llega el cliente %d ***"
                    ANSI_COLOR_RESET
                    "\n",
                    getpid());
            stat_env = mq_send(cola_c, (const char *) &m_c, sizeof(mensaje), 0);

            // Mirar la bandera de retorno, si tuvo exito en encolarse pide
            // un numero y espera a ser atendido. Si no tuvo exito sale.
            if (stat_env != 0){
                // atrib_c.mq_flags == EAGAIN
                printf("No hay lugar, sale de la tienda\n");
            } else {
                // Espera confirmación.
                mq_receive(cola_p, (char *) &m_p, sizeof(mensaje), NULL);
            }
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
