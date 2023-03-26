#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"



Lexer* create_lexer(char *input) {
	struct Lexer *lexer = malloc(sizeof(struct Lexer));
	lexer->source = input;
	lexer->curChar = '\0';
	lexer->curPos = -1;
	lexer->nextChar = &nextChar;
	lexer->peek = &peek;
	lexer->nextChar(lexer);
	return lexer;
}


void nextChar(struct Lexer* lexer) {
	lexer->curPos = lexer->curPos + 1;
	if (lexer->curPos >= strlen(lexer->source)) {
		lexer->curChar = '\0';		
	} else {
		lexer->curChar = lexer->source[lexer->curPos];
	}
}	

char peek(struct Lexer* lexer) {
	if(lexer->curPos + 1 >= strlen(lexer->source)){
		return '\0';
	}
	return lexer->source[lexer->curPos + 1];
}

void abort_lex(struct Lexer* lexer) {
	
}

void skipWhiteSpace(struct Lexer* lexer) {

}

void skipComment(struct Lexer* lexer) {

}

Token getToken(struct Lexer* lexer) {
	
}

TokenType checkIfKeyword(char tokenText) {

}


