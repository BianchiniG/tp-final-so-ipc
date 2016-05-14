#include "comun.h"

// Manejador de señales.
void sig(int s);

// Bandera de atención (Global, se debe resetear en cada cliente).
int atendiendose = 0;

int main() {
    // Variables locales del cliente
    mqd_t cola_barbero;
    mqd_t cola_cliente;
    int estado;     // Para chequear la bandera de cola llena.

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

    // Define que va a recibir la señal SIGUSR1 y el manejador.
    signal(SIGUSR1, sig);

    // Crea las colas (O se anota en ellas si ya estan creadas).
    cola_barbero = mq_open(COLA_BARBERO, O_CREAT | O_RDWR, 0600, &attr_barbero);
    cola_cliente = mq_open(COLA_CLIENTE, O_CREAT | O_NONBLOCK | O_RDWR, 0600, &attr_cliente);

    while (1) {

        if ( fork() ) {    // Padre
            // Retardo entre cada llegada de un cliente.
            sleep(3);
        } else {    // Hijo
            // Intenta inscribirse en la cola de clientes (Sala de espera).
            estado = mq_send(cola_cliente, (const char *) &m_cliente, sizeof(mensaje), 0);

            if (estado == 0) {    // Hay lugar.
                // Pone en el mensaje su pid para enviarlo al barbero.
                m_barbero.pid = getpid();
                mq_send(cola_barbero, (const char *) &m_barbero, sizeof(mensaje), 0);

                // Avisa que llegó.
                printf(ANSI_COLOR_YELLOW
                    "Cliente %d: Llegue!"
                    ANSI_COLOR_RESET
                    "\n",
                    getpid());

                    // Espera a ser atendido.
                    while(!atendiendose)
                    ;

                    // Reinicia la flag.
                    atendiendose = 0;

                    // Avisa que fue atendido.
                    printf(ANSI_COLOR_YELLOW
                        "Cliente %d: Me atendió!"
                        ANSI_COLOR_RESET
                        "\n",
                        getpid());
            } else {    // Si no había lugar.
                if (attr_cliente.mq_maxmsg == EAGAIN)
                    printf("Cliente %d: No hay lugar! *Sale de la tienda*\n", getpid());
            }
        }
    }

    return 0;
}

void sig(int s) {
    atendiendose = 1;
}
