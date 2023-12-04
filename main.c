#include "lex.h"
#include <stdio.h>
#include <string.h>


int main() {
	char *input = "-+<===!=\"halo\"";
	Lexer* lexer = create_lexer(input);
	Token token;
	while (lexer->curChar != '\0') {
		printf("%c", lexer->curChar);
		token = lexer->getToken(lexer);
		printf("%d", token.type);
	}
	return 0;
}
