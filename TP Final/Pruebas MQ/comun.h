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

// Constantes
#define MAX_BUFFER 10
#define COLA_C "/mq_testbarb"
#define COLA_P "/mq_testcli"

// Colores para la consola
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Estructura del mensaje
typedef struct {
    int pid;
    int num;
} mensaje;

// Variables de las colas
struct mq_attr atrib_c;
struct mq_attr atrib_p;
mensaje m_p;
mensaje m_c;
