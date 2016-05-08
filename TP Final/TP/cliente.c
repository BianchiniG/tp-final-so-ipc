#include "common.h"

int main(int argc, char const *argv[]) {

    char buffer_b[MAX_BUFFER];
    char buffer_c[MAX_BUFFER];
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

    // Crea la cola.
    barbero = mq_open(BARBERO_MQ, O_CREAT | O_RDWR, 0600, &attr_b);
    cliente = mq_open(CLIENTE_MQ, O_CREAT | O_RDWR, 0600, &attr_c);

    /*
    // Inicia la comunicación con la interfaz gráfica.
    iniciar(argc, argv, &m);

    */

    // --- INICIO DEL PROGRAMA --- //
    while(1){
        // Envía mensaje al barbero.
        mq_send(barbero, (char *) &buffer_b, sizeof(buffer_b), 0);

        // Espera la confirmación del barbero.
        mq_receive(cliente, (char *) &buffer_c, sizeof(buffer_c), 0);

        printf("Cliente atendiendose!");
        
        sleep(5);
    }

    return 0;
}
