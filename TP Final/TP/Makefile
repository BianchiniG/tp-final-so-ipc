
all: barbero cliente

barbero: comun.h comm.h
	gcc comm.c barbero.c -o barbero -lrt

cliente: comun.h comm.h
	gcc comm.c cliente.c -o cliente -lrt

clean:
	rm barbero cliente *.o
