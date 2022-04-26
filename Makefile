CC=gcc
CFLAGS=-I. -Wall -Wno-unknown-pragmas -finput-charset=UTF-8 -fexec-charset=UTF-8 -pedantic 
LIBS= -lm

all: build clean exec

build: main map
	$(CC) -o gcproj.exe main.o map.o $(CFLAGS) $(LIBS)

main:
	$(CC) -o main.o -c src/main.c $(CFLAGS) $(LIBS)

map:
	$(CC) -o map.o -c src/lib/map.c $(CFLAGS) $(LIBS)


clean:
	rm -f *.o

exec:
	./gcproj.exe

.PHONY: clean
