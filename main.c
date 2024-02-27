#include "lex.h"
#include <stdio.h>
#include <stdlib.h> // for malloc, free

int main() {
  FILE *pSource = fopen("./source.txt", "r");

  fseek(pSource, 0, SEEK_END);
  long file_size = ftell(pSource);
  rewind(pSource);

  char* buffer = (char*)malloc(sizeof(char) * file_size);

  size_t num_read = fread(buffer, 1, file_size, pSource);

  buffer[file_size] = '\0';

  Lexer *lexer = create_lexer(buffer);

  if (lexer == NULL) {
    fprintf(stderr, "Failed to create lexer\n");
    return 1; // Exit with error code
  }

  while (lexer->curChar != '\0') {
    Token *token = getToken(lexer);
    if (token == NULL) {
      fprintf(stderr, "Failed to get token\n");
      break; // Exit loop if getToken fails
    }
    printf("%s\n", token->text);
  }

  free(lexer);
  return 0;
}
