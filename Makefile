CC=gcc
CFLAGS=-I. -Wall -Wno-unknown-pragmas -finput-charset=UTF-8 -fexec-charset=UTF-8 -pedantic -Wno-unused-command-line-argument
LIBS= -lm

all: build clean exec

build: main map prim
	$(CC) -o gcproj.exe main.o map.o prim.o $(CFLAGS) $(LIBS)

main:
	$(CC) -o main.o -c src/main.c $(CFLAGS) $(LIBS)

map:
	$(CC) -o map.o -c src/lib/map.c $(CFLAGS) $(LIBS)

prim:
	$(CC) -o prim.o -c src/lib/prim.c $(CFLAGS) $(LIBS)


clean:
	rm -f *.o

exec:
	./gcproj.exe

.PHONY: clean
