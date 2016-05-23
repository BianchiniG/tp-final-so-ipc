#include "comun.h"
#include "comm.h"

void inicializarBarbero(TMensaje mens);

int main(int argc, char *argv[]) {
    // Variables locales del barbero.
    mqd_t cola_barbero;
    mqd_t cola_cliente;
    int duracion_turno;
    int estado, count;

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

    // Crea las colas.
    cola_barbero = mq_open(COLA_BARBERO, O_CREAT | O_RDWR, 0600, &attr_barbero);
    cola_cliente = mq_open(COLA_CLIENTE, O_CREAT | O_NONBLOCK | O_RDWR, 0600, &attr_cliente);

    // Crea semilla para tiempo random.
    srand(time(NULL));

    TMensaje mens;
    iniciar(argc, argv, &mens);

    inicializarBarbero(mens);

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

        // Envía al cliente señal de que terminó..
        estado = kill(m_barbero.pid, SIGUSR1);

    }

    return 0;
}

void inicializarBarbero(TMensaje mens) {
    // Compone el primer mensaje.
    mens.pid = getpid();
    strcpy(mens.imagen, "./Chars/barbero_derecha.zip");
    mens.x = -320;
    mens.y = 0;
    enviar(&mens);

    // Avanza hasta la silla.
        while (mens.x <= 320) {     // Avanza en x.
            if (mens.x % 2 == 0)
                usleep(15000);
            mens.x += 1;
            enviar(&mens);
        }
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, "./Chars/barbero_atras.zip");
        while (mens.y <= 80) {      // Avanza en y.
            if (mens.y % 2 == 0)
                usleep(15000);
            mens.y += 1;
            enviar(&mens);
        }
        // El barbero se ubica en su puesto
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, "./Chars/barbero.png");
        enviar(&mens);
}
