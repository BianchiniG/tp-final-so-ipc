
all: productor consumidor

productor: productor.c comun.h
	gcc productor.c -o productor -lrt

consumidor: consumidor.c comun.h
	gcc consumidor.c -o consumidor -lrt

clean:
	rm productor consumidor *.o
