# -*- Makefile -*-

.PHONY: clean

# Target: dependencies
#	action

compiler: lex.o main.o parser.o
	gcc lex.o parser.o main.o -o compiler

lex.o: lex.c lex.h
	gcc -c lex.c

parser.o: parser.c parser.h
	gcc -c parser.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o compiler

