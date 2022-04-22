all: build exec

build:
	gcc src/main.c -o out

exec:
	./out
     