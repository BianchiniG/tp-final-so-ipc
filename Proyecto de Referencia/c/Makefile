# Cambiar los nombres de los procesos
#
#
BIN_TAIL=$(shell uname -sm | tr '[:upper:]' '[:lower:]' | sed 's/\s/\./')

.PHONY: all

EJECUTABLES=prog_a prog_b

TARGETS=$(foreach a,${EJECUTABLES},$a.${BIN_TAIL})

.PHONY: all platform

all: platform


platform: ${TARGETS}

# Compilar la librería de comunicaciones con Processing
comm.${BIN_TAIL}.o: comm.c comm.h
	gcc -Wall -c comm.c -o $@

# Compilador genérico de archivos C
#%.${BIN_TAIL}: %.c comm.o
#%: %.c comm.o
#	gcc -o $@ $^

%.${BIN_TAIL}: %.c comm.${BIN_TAIL}.o
	gcc $< comm.${BIN_TAIL}.o -o $@

clean:
	-rm *.o ${TARGETS}

re: clean all

debug:
	@echo ${BIN_TAIL}
	@echo ${TARGETS}
