CC=gcc
CFLAGS=-g -Wall -I. `mysql_config --cflags --libs`

haabnexa: ./src/haabnexa.o ./libs/openserial.o ./libs/writeserial.o ./libs/setserial.o
	$(CC) -o ./bin/haabnexa ./src/haabnexa.o ./libs/openserial.o ./libs/writeserial.o ./libs/setserial.o $(CFLAGS)

clean:
	rm -f *.o

install:
	cp ./bin/haabnexa /usr/local/bin
