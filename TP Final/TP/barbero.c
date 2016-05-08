#include "common.h"

int main(int argc, char const *argv[]) {

    char buffer_b[MAX_BUFFER];
    char buffer_c[MAX_BUFFER];

    // Variables de mqueue.
    mqd_t barbero, cliente;
    struct mq_attr attr_b;
    attr_b.mq_flags = 0;
    attr_b.mq_maxmsg = 5;
    attr_b.mq_msgsize = sizeof(mens_barb_cli);
    attr_b.mq_curmsgs = 0;
    struct mq_attr attr_c;
    attr_c.mq_flags = 0;
    attr_c.mq_maxmsg = 5;
    attr_c.mq_msgsize = sizeof(mens_barb_cli);
    attr_c.mq_curmsgs = 0;

    // Variables de mensaje.
    TMensaje m;

    // Crea la cola. (Necesario un return -1 si falla para kivy).
    barbero = mq_open(BARBERO_MQ, O_CREAT | O_RDWR, 0600, &attr_b);
    cliente = mq_open(CLIENTE_MQ, O_CREAT | O_RDWR, 0600, &attr_c);

    /*
    // Inicia la comunicación con la interfaz gráfica.
    iniciar(argc, argv, &m);

    // Completa el arreglo de imágenes (MACRO).
    strcpy(m.imagenes, ????)

    // Envia mensaje a la interfaz gráfica.
    enviar(&m);
    */

    // --- INICIO DEL PROGRAMA --- //
    while(1){
        int count = 0;

        // EL barbero inicia en espera de un mensaje.
        mq_receive(barbero, (char *) &buffer_b, attr_b.mq_msgsize, 0);

        /* */
        // Acá la lógica es:
        // Un cliente le envia al barbero que esta disponible
        printf("Cliente recibido!");
        // El barbero le avisa que también esta disponible.
        mq_send(cliente, (char *) &buffer_c, attr_c.mq_msgsize, 0);
        // El cliente gráficamente se mueve hasta la silla del barbero
        // Comienza el turno del cliente.
        /* */

        // Lógica del turno.

    }

    return 0;
}
