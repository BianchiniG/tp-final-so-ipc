// Includes de la librería estándar.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

// Includes de MQueue
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

// Includes de usuario
#include "comm.h"

// Defines
#define MAX_IMG    27
#define MAX_BUFFER 10
#define BARBERO_MQ "/mq_barb"
#define CLIENTE_MQ "/mq_cli"

// Estructura para el mensaje entre el barbero y el cliente
typedef struct {
    char imagenes[MAX_IMG]; // Posiblemente char*
    char mensaje;
    int pid;
    int id;
} mens_barb_cli;
