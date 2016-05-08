#include "comun.h"

int main() {

    // Define las variables para las colas de mensajes del barbero y clientes
    mqd_t cola_c;
    mqd_t cola_p;
    char buffer[MAX_BUFFER] = "Mensaje";
    struct mq_attr atrib_c;
    struct mq_attr atrib_p;
    mensaje m_p;
    mensaje m_c;

    // Inicializa los atributos de la cola del consumidor.
    atrib_c.mq_flags = 0;
    atrib_c.mq_maxmsg = 5;
    atrib_c.mq_msgsize = sizeof(mensaje);
    atrib_c.mq_curmsgs = 0;

    // Inicializa los atributos de la cola del productor.
    atrib_c.mq_flags = 0;
    atrib_c.mq_maxmsg = 5;
    atrib_c.mq_msgsize = sizeof(mensaje);
    atrib_c.mq_curmsgs = 0;

    // Crea las colas.
    cola_c = mq_open(COLA_C, O_CREAT | O_RDWR, 0600, &atrib_c);
    cola_p = mq_open(COLA_P, O_CREAT | O_RDWR, 0600, &atrib_p);

    while(1) {
        int estado;

        if (fork()){
            waitpid(0, &estado, 0);
        } else {
            m_c.pid = getpid();

            printf("*** Llega el cliente %d ***\n", getpid());
            mq_send(cola_c, (const char *) &m_c, sizeof(mensaje), 0);

            // Espera confirmación.
            mq_receive(cola_p, (char *) &m_p, sizeof(mensaje), NULL);
        }

        sleep(1);
    }

    return 0;
}
