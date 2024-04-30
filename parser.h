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

bool checkToken(Parser *parser, int tokenType);

bool checkPeek(Parser *parser, int tokenType);

void match(Parser *parser, int tokenType);

void nextToken(Parser *parser);

void program(Parser *parser);

void statement(Parser *parser);

void expression(Parser *parser);

void comparison(Parser *parser);

void term(Parser *parser);

void unary(Parser *parser);

void primary(Parser *parser);

void newline(Parser *parser);

#endif // !PARSER_H
