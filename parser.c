/*
 * --GRAMMAR--
 *
 * program ::= {statement}
 * statement ::= "PRINT" (expression | string) nl
 *    | "LET" ident "=" expression nl
 *    | "IF" comparison "THEN" nl {statement} "ENDIF" nl
 *    | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
 * comparison ::= expression (("==" | "!=" | "<" | ">" | "<=" | ">=")
 * expression)+ 
 * expression  ::= term {("-" | "+") term} 
 * term ::= unary {("/" | "*") unary} 
 * unary ::= ["+" | "-"] primary 
 * primary ::= number | ident 
 * nl ::= '\n'+
 * */

#include "parser.h"
#include "lex.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Parser *createParser(Lexer *lexer) {
  Parser *parser = (Parser *)malloc(sizeof(Parser));
  parser->lexer = lexer;
  parser->currToken = (Token *)malloc(sizeof(Token));
  parser->peekToken = (Token *)malloc(sizeof(Token));
  nextToken(parser);
  nextToken(parser);
  return parser;
}

bool checkToken(Parser *parser, int tokenType) {
  return tokenType == parser->currToken->type;
}

bool checkPeek(Parser *parser, int tokenType) {
  return tokenType == parser->peekToken->type;
}

void nextToken(Parser *parser) {
  parser->currToken = parser->peekToken;
  parser->peekToken = getToken(parser->lexer);
}

void match(Parser *parser, int tokenType) {
  if (!checkToken(parser, tokenType)) {
    printf("%s", "Syntax Error\n");
  } else {
    nextToken(parser);
  }
}

void program(Parser *parser) {
  puts("Program\n");

  while (!checkToken(parser, EOF_TOKEN)) {
    statement(parser);
  }
}

void statement(Parser *parser) {
  // For print statement
  if (checkToken(parser, PRINT)) {
    puts("PRINT STATEMENT\n");
    nextToken(parser);
    if (checkToken(parser, STRING)) {
      nextToken(parser);
    } else {
      expression(parser);
      nextToken(parser);
    }
  } else if(checkToken(parser, IF)) {
    nextToken(parser);
    comparison(parser);

    match(parser, THEN);

    newline(parser);

    while (!checkToken(parser, ENDIF)) {
      statement(parser);
    }

    match(parser, ENDIF);
  }

  newline(parser);
}

void expression(Parser *parser) {
  puts("Expresion\n");
}

void comparison(Parser *parser) {
  puts("Comparision\n");
}

void unary(Parser *parser) {

}

void primary(Parser *parser) {
}

void term(Parser *parser) {
}

void newline(Parser *parser) {
  puts("NEWLINE\n");
  match(parser, NEWLINE);

  while(checkToken(parser, NEWLINE)) {
    nextToken(parser);
  }
}
