
all: mq_producer mq_consumer

mq_producer: mq_producer.o
	gcc -o mq_producer -lrt mq_producer.o

mq_producer.o: mq_producer.c prod_cons.h
	gcc -c mq_producer.c -o mq_producer.o

mq_consumer: mq_consumer.o
	gcc -o mq_consumer -lrt mq_consumer.o

mq_consumer.o: mq_consumer.c prod_cons.h
	gcc -c mq_consumer.c -o mq_consumer.o

clean:
	rm mq_producer mq_consumer *.o

