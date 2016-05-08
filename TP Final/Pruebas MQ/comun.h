// Includes de la librería estándar.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

// Includes de MQueue
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#define MAX_BUFFER 10
#define COLA_C "/mq_testbarb"
#define COLA_P "/mq_testcli"

// Estructura del mensaje
typedef struct {
    int pid;
    int num;
} mensaje;

struct mq_attr atrib_c;
struct mq_attr atrib_p;
