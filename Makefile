CC=gcc
CFLAGS=-w --std=c99 -g
LIBS=-ldl -lssl -lcrypto
OUT=murder-detective

.PHONY=run

functions.o: src/functions.c
	$(CC) src/functions.c $(CFLAGS) $(LIBS) -c -o src/functions.o

all: functions.o
	$(CC) src/functions.o src/murder-detective.c $(CFLAGS) $(LIBS) -o $(OUT)

clean: all
	rm src/*.o

run: clean
	./$(OUT)