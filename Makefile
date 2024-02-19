# -*- Makefile -*-

.PHONY: clean

# Target: dependencies
#	action

compiler: lex.o main.o
	gcc lex.o main.o -o compiler

lex.o: lex.c
	gcc -c lex.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o compiler

