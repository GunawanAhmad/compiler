#include "lex.h"
#include "parser.h"
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

  Parser *parser = createParser(lexer);
  program(parser);

  free(lexer);
  return 0;
}
