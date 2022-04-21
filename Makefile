all: build exec

build:
	gcc -c main.c -o gcproj

exec:
	chmod +x gcproj
	./gcproj
