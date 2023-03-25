#include <stdio.h>
#include <string.h>



typedef enum TokenType {
	EOF_TOKEN = -1,
	NEWLINE = 0,
	NUMBER = 1,
	IDENT = 2,
	STRING = 3,

	// keyword
	PRINT = 103,
	IF = 106,
	THEN = 107,
	REPEAT = 109,
	WHILE = 110,
	ENDIF = 111,
	ENDWHILE = 112,

	// Operators
	MINUS = 201,
	PLUS = 202,
	ASTERISK = 203,
	SLASH = 204,
	EQ = 205,
	EQEQ = 206,
	LT = 207,
	LTEQ = 208,
	GT = 209,
	GTEQ = 201,
	NOTEQ = 211,
}

struct Token {
	char* text;
	enum TokenType type;
}


typedef struct Lexer {
	char* source;
	char curChar;
	int curPos;
	
	// Advance to the next char
	void (*nextChar)(struct Lexer*);
	
	// Return the lookeahead char
	char (*peek)(struct Lexer*);

	// Invalid token found, print error and exit
	void (*abort)(struct Lexer*);

	//skip whitespaces except newline, which we will use to indicate the end of the statement
	void (*abort)(struct Lexer*);

	//skip comment in the code
	void (*skipComment)(struct Lexer*);

	// Return the next token
	char (*getToken)(struct Lexer*);
} Lexer;


typedef struct Token {
	TokenType (*checkIfKeyword)(struct Lexer*) 
} Token


