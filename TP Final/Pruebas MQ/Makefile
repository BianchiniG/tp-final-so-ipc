
all: productor consumidor

productor: productor.o
	gcc -o productor -lrt productor.o

productor.o: productor.c comun.h
	gcc -c productor.c -o productor.o

consumidor: consumidor.o
	gcc -o consumidor -lrt consumidor.o

consumidor.o: consumidor.c comun.h
	gcc -c consumidor.c -o consumidor.o

clean:
	rm productor consumidor *.o
