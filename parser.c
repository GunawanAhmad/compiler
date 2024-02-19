/*
 * --GRAMMAR--
 *
 * program ::= {statement}
 * statement ::= "PRINT" (expression | string) nl
 *    | "LET" ident "=" expression nl
 *    | "IF" comparison "THEN" nl {statement} "ENDIF" nl
 *    | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
 * comparison ::= expression (("==" | "!=" | "<" | ">" | "<=" | ">=")
 * expression) + expression  ::= term {("-" | "+") term} term ::= unary {("/" |
 * "*") unary} unary ::= ["+" | "-"] primary primary ::= number | ident nl ::=
 * '\n' +
 * */

#include "parser.h"
#include "lex.h"
#include <stdbool.h>
#include <stdlib.h>

Parser *createParser(Lexer *lexer) {
  Parser *parser = (Parser *)malloc(sizeof(Parser));
  parser->lexer = lexer;
  parser->currToken = (Token *)malloc(sizeof(Token));
  parser->peekToken = (Token *)malloc(sizeof(Token));
  return parser;
}

bool checkToken(Parser *parser, Token token) {
  return token.type == parser->currToken->type;
}

bool checkPeek(Parser *parser, Token token) {
  return token.type == parser->peekToken->type;
}
