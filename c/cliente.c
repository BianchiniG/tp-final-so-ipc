#include "comun.h"
#include "comm.h"

// Funciones.
void sig(int s);

// Bandera de atención.
int atendiendose = 0;

int main(int argc, char *argv[]) {
    // Variables locales del cliente
    mqd_t cola_barbero;
    mqd_t cola_cliente;
    TMensaje mens;
    int asiento,
        num_personaje,
        stat_env;     // Para chequear la bandera de cola llena.

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

    // Crea semilla para numeros random.
    srand(time(NULL));
    num_personaje = (rand() % 3) + 1;

    // Define que va a recibir la señal SIGUSR1 y el manejador.
    signal(SIGUSR1, sig);

    // Crea las colas (O se anota en ellas si ya estan creadas).
    cola_barbero = mq_open(COLA_BARBERO, O_CREAT | O_RDWR, 0600, &attr_barbero);
    cola_cliente = mq_open(COLA_CLIENTE, O_CREAT | O_NONBLOCK | O_RDWR, 0600, &attr_cliente);

    // Inicia comunicación.
    iniciar(argc, argv, &mens);

    // Cliente entra en la barbería:
    memset(mens.imagen, '\0', sizeof(mens.imagen));
    if (num_personaje == 1) {
        strcpy(mens.imagen, "./Chars/char1_largo/char1_largo_derecha.zip");
    } else if (num_personaje == 2) {
        strcpy(mens.imagen, "./Chars/char2_largo/char2_largo_derecha.zip");
    } else if (num_personaje == 3) {
        strcpy(mens.imagen, "./Chars/char3_largo/char3_largo_derecha.zip");
    } else if (num_personaje == 4) {
        strcpy(mens.imagen, "./Chars/char4_largo/char4_largo_derecha.zip");
    }
    mens.pid = getpid();
    mens.x = -320;
    mens.y = 0;
    enviar(&mens);

    // Intenta inscribirse en la cola de clientes (Sala de espera).
    stat_env = mq_send(cola_cliente, (const char *) &m_cliente, sizeof(mensaje), 0);

    if (stat_env == 0) {    // Hay lugar.
        // Pone en el mensaje su pid para enviarlo al barbero.
        m_barbero.pid = getpid();
        mq_send(cola_barbero, (const char *) &m_barbero, sizeof(mensaje), 0);

        // Avisa que llegó.
        printf(ANSI_COLOR_YELLOW "Cliente %d: Llegue!" ANSI_COLOR_RESET "\n", getpid());

        // El cliente avanza hasta la sala de espera.
        while (mens.x <= -160) {
            if (mens.x % 2 == 0)
                usleep(15000);
            mens.x += 1;
            enviar(&mens);
        }

        // Espera a ser atendido.
        while(!atendiendose) {
            // Se sienta y espera a que lo atiendan.
        }

        // Es atendido.
        printf(ANSI_COLOR_YELLOW "Cliente %d: Me atendió!" ANSI_COLOR_RESET "\n", getpid());
        while(atendiendose) {
            // Se sienta en la silla del barbero, etc.
        }

    } else {    // Si no había lugar.
        printf("Cliente %d: No hay lugar! *Sale de la tienda*\n", getpid());
    }

    // Cliente sale de la barbería:
    memset(mens.imagen, '\0', sizeof(mens.imagen));
    if (num_personaje == 1) {
        strcpy(mens.imagen, "./Chars/char1_corto/char1_corto_izquierda.zip");
    } else if (num_personaje == 2) {
        strcpy(mens.imagen, "./Chars/char2_corto/char2_corto_izquierda.zip");
    } else if (num_personaje == 3) {
        strcpy(mens.imagen, "./Chars/char3_corto/char3_corto_izquierda.zip");
    } else if (num_personaje == 4) {
        strcpy(mens.imagen, "./Chars/char4_corto/char4_corto_izquierda.zip");
    }
    while (mens.x > -340) {
        if (mens.x % 2 == 0)
            usleep(15000);
        mens.x--;
        enviar(&mens);
    }

    // Mata al proceso del cliente.
    mens.estado = -1;
    enviar(&mens);

    return 0;
}

void sig(int s) {
    if (atendiendose == 0){
        atendiendose = 1;
    } else {
        atendiendose = 0;
    }
}
