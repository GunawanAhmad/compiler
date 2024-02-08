#include "lex.h"
#include <stdio.h>

int main() {
  char *input = "-+<===!=\"halo\"WHILE GUNA";
  Lexer *lexer = create_lexer(input);
  Token token;
  while (lexer->curChar != '\0') {
    token = lexer->getToken(lexer);
    printf("%s ", token.text);
    printf("%d\n", token.type);
  }
  return 0;
}
