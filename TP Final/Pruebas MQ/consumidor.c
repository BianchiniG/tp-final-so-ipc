#include "comun.h"

int main() {

    // Define las variables para la cola de mensajes del barbero y clientes
    mqd_t cola_c;
    mqd_t cola_p;
    // mqd_t cola_count;
    // mqd_t cola_prior;
    char buffer[MAX_BUFFER];

    // Crea la cola.
    cola_c = mq_open(COLA_C, O_CREAT | O_RDWR, 0600, &atrib_c);
    cola_p = mq_open(COLA_P, O_CREAT | O_RDWR, 0600, &atrib_b);

    while(1) {
        mq_receive(cola_c, (char *) &m_c, sizeof(mensaje), NULL);

        printf(ANSI_COLOR_RED
                "Barbero: Me llamo el cliente %d"
                ANSI_COLOR_RESET
                "\n",
                m_c.pid);

        // Envía al cliente señal de que lo va a atender.
        mq_send(cola_p, (const char *) &m_p, sizeof(mensaje), 0);

        printf(ANSI_COLOR_GREEN
                "Barbero: Atendiendo al cliente %d"
                ANSI_COLOR_RESET
                "\n",
                m_c.pid);

        sleep(10);

    }

    return 0;
}
