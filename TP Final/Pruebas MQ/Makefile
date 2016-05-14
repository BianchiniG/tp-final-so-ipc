
all: barbero cliente

barbero: barbero.o
	gcc -o barbero -lrt barbero.o

barbero.o: barbero.c comun.h
	gcc -c barbero.c -o barbero.o

cliente: cliente.o
	gcc -o cliente -lrt cliente.o

cliente.o: cliente.c comun.h
	gcc -c cliente.c -o cliente.o
productor: productor.c comun.h
	gcc productor.c -o productor -lrt

consumidor: consumidor.c comun.h
	gcc consumidor.c -o consumidor -lrt

clean:
	rm barbero cliente *.o
