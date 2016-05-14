#include "comun.h"

int main() {

    // Define las variables para la cola de mensajes del barbero y clientes
    mqd_t cola;
    char buffer[MAX_BUFFER];
    int estado;

    // Crea la cola.
    cola = mq_open(COLA_C, O_CREAT | O_RDWR, 0600, &atrib);

    while(1) {
        mq_receive(cola, (char *) &m, sizeof(mensaje), NULL);

        printf(ANSI_COLOR_RED
                "Barbero: Me llamo el cliente %d"
                ANSI_COLOR_RESET
                "\n",
                m.pid);

        // Envía al cliente señal de que lo va a atender.
        estado = kill(m.pid, SIGUSR1);

        printf(ANSI_COLOR_GREEN
                "Barbero: Atendiendo al cliente %d"
                ANSI_COLOR_RESET
                "\n",
                m.pid);

        sleep(10);

    }

    return 0;
}
