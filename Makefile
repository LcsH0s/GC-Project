CC=gcc
CFLAGS=-I. -Wall -Wno-unused-command-line-argument
LIBS= -lm

all: build clean

build: main map prim compression
	$(CC) -o gcproj.exe main.o map.o prim.o compression.o $(CFLAGS) $(LIBS)

main:
	$(CC) -o main.o -c src/main.c $(CFLAGS) $(LIBS)

map:
	$(CC) -o map.o -c src/lib/map.c $(CFLAGS) $(LIBS)

prim:
	$(CC) -o prim.o -c src/lib/prim.c $(CFLAGS) $(LIBS)

compression:
	$(CC) -o compression.o -c src/lib/compression.c $(CFLAGS) $(LIBS)

clean:
	rm -f *.o

.PHONY: clean
