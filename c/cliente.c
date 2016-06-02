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
    int num_personaje,
        stat_env;     // Para chequear la bandera de cola llena.
    // Variables contenedoras para las imágenes del pj.
    char img_pj_frente_largo[80];
    char img_pj_izquierda_largo[80];
    char img_pj_derecha_largo[80];
    char img_pj_atras_largo[80];
    char img_pj_frente_corto[80];
    char img_pj_izquierda_corto[80];
    char img_pj_derecha_corto[80];
    char img_pj_atras_corto[80];
    char img_pj_sentado_frente[80];
    char img_pj_atendido[80];

    // Atributos de las colas.
    struct mq_attr attr_barbero;
        attr_barbero.mq_flags = 0;
        attr_barbero.mq_maxmsg = 3;
        attr_barbero.mq_msgsize = sizeof(mensaje);
        attr_barbero.mq_curmsgs = 0;
    struct mq_attr attr_cliente;
        attr_cliente.mq_flags = 0;
        attr_cliente.mq_maxmsg = 3;
        attr_cliente.mq_msgsize = sizeof(mensaje);
        attr_cliente.mq_curmsgs = 0;

    // Crea semilla para numeros random.
    srand(time(NULL));
    num_personaje = (rand() % 4) + 1;
    // Asigna las imágenes del pj sorteado.
    if (num_personaje == 1)
    {
        strcpy(img_pj_frente_largo, "./Chars/char1_largo/char1_largo_frente.zip");
        strcpy(img_pj_izquierda_largo, "./Chars/char1_largo/char1_largo_izquierda.zip");
        strcpy(img_pj_derecha_largo, "./Chars/char1_largo/char1_largo_derecha.zip");
        strcpy(img_pj_atras_largo, "./Chars/char1_largo/char1_largo_atras.zip");
        strcpy(img_pj_frente_corto, "./Chars/char1_corto/char1_corto_frente.zip");
        strcpy(img_pj_izquierda_corto, "./Chars/char1_corto/char1_corto_izquierda.zip");
        strcpy(img_pj_derecha_corto, "./Chars/char1_corto/char1_corto_derecha.zip");
        strcpy(img_pj_atras_corto, "./Chars/char1_corto/char1_corto_atras.zip");
        strcpy(img_pj_sentado_frente, "./Chars/char1_largo/char1_sentado_frente.png");
        strcpy(img_pj_atendido, "./Chars/char1_largo/char1_atendiendose.png");
    }
    else if (num_personaje == 2)
    {
        strcpy(img_pj_frente_largo, "./Chars/char2_largo/char2_largo_frente.zip");
        strcpy(img_pj_izquierda_largo, "./Chars/char2_largo/char2_largo_izquierda.zip");
        strcpy(img_pj_derecha_largo, "./Chars/char2_largo/char2_largo_derecha.zip");
        strcpy(img_pj_atras_largo, "./Chars/char2_largo/char2_largo_atras.zip");
        strcpy(img_pj_frente_corto, "./Chars/char2_corto/char2_corto_frente.zip");
        strcpy(img_pj_izquierda_corto, "./Chars/char2_corto/char2_corto_izquierda.zip");
        strcpy(img_pj_derecha_corto, "./Chars/char2_corto/char2_corto_derecha.zip");
        strcpy(img_pj_atras_corto, "./Chars/char2_corto/char2_corto_atras.zip");
        strcpy(img_pj_sentado_frente, "./Chars/char2_largo/char2_sentado_frente.png");
        strcpy(img_pj_atendido, "./Chars/char2_largo/char2_atendiendose.png");
    }
    else if (num_personaje == 3)
    {
        strcpy(img_pj_frente_largo, "./Chars/char3_largo/char3_largo_frente.zip");
        strcpy(img_pj_izquierda_largo, "./Chars/char3_largo/char3_largo_izquierda.zip");
        strcpy(img_pj_derecha_largo, "./Chars/char3_largo/char3_largo_derecha.zip");
        strcpy(img_pj_atras_largo, "./Chars/char3_largo/char3_largo_atras.zip");
        strcpy(img_pj_frente_corto, "./Chars/char3_corto/char3_corto_frente.zip");
        strcpy(img_pj_izquierda_corto, "./Chars/char3_corto/char3_corto_izquierda.zip");
        strcpy(img_pj_derecha_corto, "./Chars/char3_corto/char3_corto_derecha.zip");
        strcpy(img_pj_atras_corto, "./Chars/char3_corto/char3_corto_atras.zip");
        strcpy(img_pj_sentado_frente, "./Chars/char3_largo/char3_sentado_frente.png");
        strcpy(img_pj_atendido, "./Chars/char3_largo/char3_atendiendose.png");
    }
    else if (num_personaje == 4)
    {
        strcpy(img_pj_frente_largo, "./Chars/char4_largo/char4_largo_frente.zip");
        strcpy(img_pj_izquierda_largo, "./Chars/char4_largo/char4_largo_izquierda.zip");
        strcpy(img_pj_derecha_largo, "./Chars/char4_largo/char4_largo_derecha.zip");
        strcpy(img_pj_atras_largo, "./Chars/char4_largo/char4_largo_atras.zip");
        strcpy(img_pj_frente_corto, "./Chars/char4_corto/char4_corto_frente.zip");
        strcpy(img_pj_izquierda_corto, "./Chars/char4_corto/char4_corto_izquierda.zip");
        strcpy(img_pj_derecha_corto, "./Chars/char4_corto/char4_corto_derecha.zip");
        strcpy(img_pj_atras_corto, "./Chars/char4_corto/char4_corto_atras.zip");
        strcpy(img_pj_sentado_frente, "./Chars/char4_largo/char4_sentado_frente.png");
        strcpy(img_pj_atendido, "./Chars/char4_largo/char4_atendiendose.png");
    }

    // Define que va a recibir la señal SIGUSR1 y el manejador.
    signal(SIGUSR1, sig);

    // Crea las colas (O se anota en ellas si ya estan creadas).
    cola_barbero = mq_open(COLA_BARBERO, O_CREAT | O_RDWR, 0600, &attr_barbero);
    cola_cliente = mq_open(COLA_CLIENTE, O_CREAT | O_NONBLOCK | O_RDWR, 0600, &attr_cliente);

    // Inicia comunicación.
    iniciar(argc, argv, &mens);

    // Cliente entra en la barbería:
    memset(mens.imagen, '\0', sizeof(mens.imagen));
    strcpy(mens.imagen, img_pj_derecha_largo);
    mens.pid = getpid();
    mens.x = -340;
    mens.y = -50;
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
        while (mens.x <= -205) {
            if (mens.x % 2 == 0)
                usleep(15000);
            mens.x += 1;
            enviar(&mens);
        }

        // ------------------------------------------------------------------ //
        // Espera a ser atendido.
        // ------------------------------------------------------------------ //
        if (!atendiendose) {
            memset(mens.imagen, '\0', sizeof(mens.imagen));
            strcpy(mens.imagen, img_pj_atras_largo);
            while (mens.y <= 50){
                if (mens.y % 2 == 0)
                usleep(15000);
                mens.y += 1;
                enviar(&mens);
            }

            memset(mens.imagen, '\0', sizeof(mens.imagen));
            strcpy(mens.imagen, img_pj_sentado_frente);
            mens.x = -205;
            mens.y = 90;
            mens.estado = 2;
            enviar(&mens);

            while(!atendiendose)
                ;   // No hace nada.

            mens.y = 50;
            mens.estado = 3;
            enviar(&mens);
        }

        // Sale de la sala de espera.
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, img_pj_frente_largo);
        enviar(&mens);
        while (mens.y > -50) {
            if (mens.y % 2 == 0)
                usleep(15000);
            mens.y -= 1;
            enviar(&mens);
        }

        // Avanza hasta la silla del barbero.
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, img_pj_derecha_largo);
        while (mens.x <= 220) {
            if (mens.x % 2 == 0)
                usleep(15000);
            mens.x += 1;
            enviar(&mens);
        }
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, img_pj_atras_largo);
        while (mens.y <= 80) {
            if (mens.y % 2 == 0)
                usleep(15000);
            mens.y += 1;
            enviar(&mens);
        }

        // ------------------------------------------------------------------ //
        // Es atendido.
        // ------------------------------------------------------------------ //
        printf(ANSI_COLOR_YELLOW "Cliente %d: Me atendió!" ANSI_COLOR_RESET "\n", getpid());
        if (atendiendose){
            // Se sienta en la silla y es atendido.
            memset(mens.imagen, '\0', sizeof(mens.imagen));
            strcpy(mens.imagen, img_pj_atendido);
            mens.pid = getpid();
            mens.x = 270;
            mens.y = 128;
            enviar(&mens);
        }
        while(atendiendose)
        ;

        // Sale de la barbería.
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, img_pj_frente_corto);
        mens.x = 220;
        mens.y = 80;
        while (mens.y > -50) {
            if (mens.y % 2 == 0)
                usleep(15000);
            mens.y -= 1;
            enviar(&mens);
        }
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, img_pj_izquierda_corto);
        while (mens.x > -340) {
            if (mens.x % 2 == 0)
            usleep(15000);
            mens.x--;
            enviar(&mens);
        }
    } else {    // Si no había lugar.
        printf("Cliente %d: No hay lugar! *Sale de la tienda*\n", getpid());

        // Sale de la barbería.
        memset(mens.imagen, '\0', sizeof(mens.imagen));
        strcpy(mens.imagen, img_pj_izquierda_largo);
        while (mens.x > -340) {
            if (mens.x % 2 == 0)
            usleep(15000);
            mens.x--;
            enviar(&mens);
        }
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
