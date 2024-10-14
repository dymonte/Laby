all: build run clean

build:
	gcc -o main main.c

run:
	./main

clean:
	rm -f main

valgrind:
	