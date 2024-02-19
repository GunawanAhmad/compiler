#ifndef PARSER_H
#define PARSER_H
#include "lex.h"
#include <stdbool.h>

typedef struct Parser {
  Lexer *lexer;
  Token *currToken;
  Token *peekToken;
} Parser;

Parser *createParser(Lexer *lexer);

bool checkToken(Parser *parser, Token token);

bool checkPeek(Parser *parser, Token token);

void match(Parser *parser, Token token);

void nextToken(Parser *parser);
#endif // !PARSER_H
