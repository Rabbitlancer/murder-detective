CC=gcc
CFLAGS=-w --std=c99 -g
LIBS=-ldl -lssl -lcrypto
OUT=murder-detective

.PHONY=all clean

functions.o: src/functions.c
	$(CC) src/functions.c $(CFLAGS) $(LIBS) -c -o src/functions.o

all: functions.o
	$(CC) src/functions.o src/murder-detective.c $(CFLAGS) $(LIBS) -o $(OUT)

clean:
	rm src/*.o

run:
	./$(OUT)