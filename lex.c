#include "lex.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer *create_lexer(char *input) {
  struct Lexer *lexer = malloc(sizeof(struct Lexer));
  lexer->source = input;
  lexer->curChar = '\0';
  lexer->curPos = -1;
  nextChar(lexer);
  return lexer;
}

TokenType checkIfKeyword(char *tokenText) {
  //strcmp will return 0 if the string is the same
  if (!strcmp(tokenText, "WHILE")) {
    return WHILE;
  } else if (!strcmp(tokenText, "IF")) {
    return IF;
  } else if (!strcmp(tokenText, "ENDIF")) {
    return ENDIF;
  } else if (!strcmp(tokenText, "PRINT")) {
    return PRINT;
  } else if (!strcmp(tokenText, "ENDWHILE")) {
    return ENDWHILE;
  } else if (!strcmp(tokenText, "ENDIF")) {
    return ENDIF;
  } else {
    return IDENT;
  }
}

Token* create_token(char *text, TokenType type) {
  struct Token *token = (Token*)malloc(sizeof(Token));
  token->text = text;
  token->type = type;
  return token;
}

void nextChar(struct Lexer *lexer) {
  lexer->curPos = lexer->curPos + 1;
  if (lexer->curPos >= strlen(lexer->source)) {
    lexer->curChar = '\0';
  } else {
    lexer->curChar = lexer->source[lexer->curPos];
  }
}

char peek(struct Lexer *lexer) {
  if (lexer->curPos + 1 >= strlen(lexer->source)) {
    return '\0';
  }
  return lexer->source[lexer->curPos + 1];
}

void abort_lex(struct Lexer *lexer) {
  char str[20] = "ERROR";
  printf("%s", str);
  exit(1);
}

void skipWhiteSpace(struct Lexer *lexer) {
  while (lexer->curChar == ' ' || lexer->curChar == '\t' ||
         lexer->curChar == '\r') {
    nextChar(lexer);
  }
}

void skipComment(struct Lexer *lexer) {
  if (lexer->curChar == '#') {
    while (lexer->curChar != '\n') {
      nextChar(lexer);
    }
  }
}

Token *getToken(struct Lexer *lexer) {
  skipWhiteSpace(lexer);
  skipComment(lexer);
  Token *token;
  if (lexer->curChar == '+') {
    char *str = "+";
    token = create_token(str, PLUS);
  } else if (lexer->curChar == '-') {
    char *str = "-";
    token = create_token(str, MINUS);
  } else if (lexer->curChar == '/') {
    char *str = "/";
    token = create_token(str, SLASH);
  } else if (lexer->curChar == '*') {
    char *str = "*";
    token = create_token(str, ASTERISK);
  } else if (lexer->curChar == '\n') {
    char *str = "\n";
    token = create_token(str, NEWLINE);
  } else if (lexer->curChar == '\0') {
    char *str = "\0";
    token = create_token(str, EOF_TOKEN);
  } else if (lexer->curChar == '=') {
    if (peek(lexer) == '=') {
      char *result = (char*)malloc(sizeof(char) * 2);
      result[0] = lexer->curChar;
      nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, EQEQ);
    } else {
      char *str = "=";
      token = create_token(str, EQ);
    }
  } else if (lexer->curChar == '<') {
    if (peek(lexer) == '=') {
      char *result = (char*)malloc(sizeof(char) * 2);
      result[0] = lexer->curChar;
      nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, LTEQ);
    } else {
      char *str = "<";
      token = create_token(str, LT);
    }
  } else if (lexer->curChar == '>') {
    if (peek(lexer) == '=') {
      char *result = (char*)malloc(sizeof(char) * 2);
      result[0] = lexer->curChar;
      nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, GTEQ);
    } else {
      char *str = ">";
      token = create_token(str, GT);
    }
  } else if (lexer->curChar == '!') {
    if (peek(lexer) == '=') {
      char *result = (char*)malloc(sizeof(char) * 2);
      result[0] = lexer->curChar;
      nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, NOTEQ);
    } else {
      abort_lex(lexer);
    }
  } else if (lexer->curChar == '\"') {
    nextChar(lexer);
    int index = 0;
    int capacity = 10;
    char *stringValue = (char *)malloc(capacity * sizeof(char));

    while (lexer->curChar != '\"') {
      if (lexer->curChar == '\r' || lexer->curChar == '\t' ||
          lexer->curChar == '\n') {
        abort_lex(lexer);
      }
      if (index >= capacity - 1) {
        capacity = capacity * 2;
        char *temp = realloc(stringValue, capacity * sizeof(char));
        stringValue = temp;
      }
      nextChar(lexer);
    }
    token = create_token(stringValue, STRING);
  } else if (isalpha(lexer->curChar)) {
    int startPos = lexer->curPos;
    int capacity = 1;
    char *tokText = (char *)malloc(sizeof(char) * (capacity));
    int index = 0;
    tokText[index] = lexer->curChar;
    while (isalnum(peek(lexer))) {
      nextChar(lexer);
      capacity++;
      char *temp = realloc(tokText, capacity);
      tokText = temp;
      index++;
      tokText[index] = lexer->curChar;
    }

    TokenType type = checkIfKeyword(tokText);
    token = create_token(tokText, type);
  } else if(isdigit(lexer->curChar)) {
    int startPos = lexer->curPos;
    int capacity = 1;
    int index = 0;
    char *tokText = (char*)malloc(sizeof(char) * capacity);
    tokText[index] = lexer->curChar;
    while(isdigit(peek(lexer))) {
      nextChar(lexer);
      capacity++;
      tokText = realloc(tokText, sizeof(char) * capacity);
      index++;
      tokText[index] = lexer->curChar;
    }
    token = create_token(tokText, NUMBER);
  }
  nextChar(lexer);
  return token;
}
