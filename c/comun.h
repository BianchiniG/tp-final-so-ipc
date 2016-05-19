#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// Librerías de mqueue.
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

// Definiciones
#define MAX_BUFFER      10
#define COLA_BARBERO    "/mq_barbero"
#define COLA_CLIENTE    "/mq_cliente"

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

//Mensajes de cada cola.
mensaje m_barbero;
mensaje m_cliente;
