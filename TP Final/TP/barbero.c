#include "comun.h"

int main() {
    // Variables locales del barbero.
    mqd_t cola_barbero;
    mqd_t cola_cliente;
    char buffer[MAX_BUFFER];
    int duracion_turno;
    int estado;

    // Atributos de las colas.
    struct mq_attr attr_barbero;
        attr_barbero.mq_flags = 0;
        attr_barbero.mq_maxmsg = 5;
        attr_barbero.mq_msgsize = sizeof(mensaje);
        attr_barbero.mq_curmsgs = 0;
    struct mq_attr attr_cliente;
        attr_cliente.mq_flags = 0;
        attr_cliente.mq_maxmsg = 5;
        attr_cliente.mq_msgsize = sizeof(mensaje);
        attr_cliente.mq_curmsgs = 0;

    // Crea semilla para tiempo random.
    srand(time(NULL));

    // Crea las colas.
    cola_barbero = mq_open(COLA_BARBERO, O_CREAT | O_RDWR, 0600, &attr_barbero);
    cola_cliente = mq_open(COLA_CLIENTE, O_CREAT | O_NONBLOCK | O_RDWR, 0600, &attr_cliente);

    while (1) {
        mq_receive(cola_barbero, (char *) &m_barbero, sizeof(mensaje), NULL);

        printf(ANSI_COLOR_RED
                "Barbero: Me llamo el cliente %d"
                ANSI_COLOR_RESET
                "\n",
                m_barbero.pid);

        // Envía al cliente señal de que lo va a atender.
        estado = kill(m_barbero.pid, SIGUSR1);

        // Reduce la cola de contador.
        mq_receive(cola_cliente, (char *) &m_cliente, sizeof(mensaje), NULL);

        printf(ANSI_COLOR_GREEN
                "Barbero: Atendiendo al cliente %d"
                ANSI_COLOR_RESET
                "\n",
                m_barbero.pid);

        // Retardo para simular lo que tarda en atender a cada cliente.
        duracion_turno = (rand() % 25) + 5;
        sleep(duracion_turno);

    }

    return 0;
}
