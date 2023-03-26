#include "lex.h"
#include <stdio.h>
#include <string.h>


int main() {
	char *input = "IF+";
	Lexer* lexer = create_lexer(input);
	while (lexer->curChar != '\0') {
		printf("%c", lexer->curChar);
		lexer->nextChar(lexer);	
	}
	printf("%s", "\n");

	return 0;

}
