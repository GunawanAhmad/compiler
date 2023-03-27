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
	lexer->getToken = &getToken;
	lexer->nextChar(lexer);
	return lexer;
}

TokenType checkIfKeyword(char tokenText) {

}


Token create_token(char *text, TokenType type) {
	struct Token token;
	token.text = text;
	token.type = type;
	token.checkIfKeyword = &checkIfKeyword;
	return token;
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
	Token token;
	if(lexer->curChar == '+') {
		token = create_token(lexer->curChar, PLUS); 
	} else if(lexer->curChar == '-') {
		token = create_token(lexer->curChar, MINUS);
	} else {
		token = create_token(lexer->curChar,IF); 
	}
	
	lexer->nextChar(lexer);
	return token;
}



