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
	lexer->abort_lex = &abort_lex;
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
	char str[20] = "ERROR";
	printf("%s", str);
	exit(1);	
}

void skipWhiteSpace(struct Lexer* lexer) {
	while(lexer->curChar == ' ' || lexer->curChar == '\t' || lexer->curChar == '\r') {
		lexer->nextChar(lexer);
	}
}

void skipComment(struct Lexer* lexer) {
	if (lexer->curChar == '#') {
		while(lexer->curChar != '\n') {
			lexer->nextChar(lexer);
		}
	}
}

Token getToken(struct Lexer* lexer) {
	skipWhiteSpace(lexer);
	skipComment(lexer);
	Token token;
	if(lexer->curChar == '+') {
		token = create_token(lexer->curChar, PLUS); 
	} else if(lexer->curChar == '-') {
		token = create_token(lexer->curChar, MINUS);
	} else if (lexer->curChar == '/'){
		token = create_token(lexer->curChar, SLASH); 
	} else if(lexer->curChar == '*') {
		token = create_token(lexer->curChar, ASTERISK);
	} else if(lexer->curChar == '\n') {
		token = create_token(lexer->curChar, NEWLINE);
	} else if(lexer->curChar == '\0') {
		token = create_token(lexer->curChar, EOF_TOKEN);
	} else if(lexer->curChar == '=') {
		if(lexer->peek(lexer) == '=') {
			char result[2];
			result[0] = lexer->curChar;
			lexer->nextChar(lexer);
			result[1] = lexer->curChar;
			token = create_token(result, EQEQ);
		} else {
			token = create_token(lexer->curChar, EQ);
		}
	} else if(lexer->curChar == '<') {
		if(lexer->peek(lexer) == '=') {
			char result[2];
			result[0] = lexer->curChar;
			lexer->nextChar(lexer);
			result[1] = lexer->curChar;
			token = create_token(result, LTEQ);
		} else {
			token = create_token(lexer->curChar, LT);
		}
	} else if(lexer->curChar == '>') {
		if(lexer->peek(lexer) == '=') {
			char result[2];
			result[0] = lexer->curChar;
			lexer->nextChar(lexer);
			result[1] = lexer->curChar;
			token = create_token(result, GTEQ);
		} else {
			token = create_token(lexer->curChar, GT);
		}
	} else if(lexer->curChar == '!') {
		if(lexer->peek(lexer) == '=') {
			char result[2];
			result[0] = lexer->curChar;
			lexer->nextChar(lexer);
			result[1] = lexer->curChar;
			token = create_token(result, NOTEQ);
		} else {
			lexer->abort_lex(lexer);
		}
	} else if(lexer->curChar == '\"') {
		lexer->nextChar(lexer);
		int index = 0;
		int capacity = 10;
		char *stringValue = (char*) malloc(capacity * sizeof(char));

		while(lexer->curChar != '\"') {
			if(lexer->curChar == '\r' || lexer->curChar == '\t' || lexer->curChar == '\n') {
				lexer->abort_lex(lexer);
			}
			if(index >= capacity - 1) {
				capacity = capacity * 2;
				char* temp = realloc(stringValue, capacity * sizeof(char));
				stringValue = temp;
			}
			printf("%c\n", lexer->curChar);
			lexer->nextChar(lexer);
		}

		token = create_token(stringValue, STRING);
	}
	
	lexer->nextChar(lexer);
	return token;
}



