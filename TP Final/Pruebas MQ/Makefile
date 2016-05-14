
all: barbero cliente

barbero: barbero.o
	gcc -o barbero -lrt barbero.o

barbero.o: barbero.c comun.h
	gcc -c barbero.c -o barbero.o

cliente: cliente.o
	gcc -o cliente -lrt cliente.o

cliente.o: cliente.c comun.h
	gcc -c cliente.c -o cliente.o

clean:
	rm barbero cliente *.o *.gch
