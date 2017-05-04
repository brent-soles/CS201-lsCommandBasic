all: cls

cls: cls.o main.o
	gcc -o cls cls.o main.o -pg

cls.o: cls.c cls.h
	gcc -g -c cls.c cls.h -pg 

main.o: main.c
	gcc -g -c main.c -pg

clean:
	rm *o cls
