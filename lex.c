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
  lexer->nextChar = &nextChar;
  lexer->peek = &peek;
  lexer->getToken = &getToken;
  lexer->abort_lex = &abort_lex;
  lexer->nextChar(lexer);
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

Token create_token(char *text, TokenType type) {
  struct Token token;
  token.text = text;
  token.type = type;
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
    lexer->nextChar(lexer);
  }
}

void skipComment(struct Lexer *lexer) {
  if (lexer->curChar == '#') {
    while (lexer->curChar != '\n') {
      lexer->nextChar(lexer);
    }
  }
}

Token getToken(struct Lexer *lexer) {
  skipWhiteSpace(lexer);
  skipComment(lexer);
  Token token;
  if (lexer->curChar == '+') {
    char ch = lexer->curChar;
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    token = create_token(str, PLUS);
  } else if (lexer->curChar == '-') {
    char ch = lexer->curChar;
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    token = create_token(str, MINUS);
  } else if (lexer->curChar == '/') {
    char ch = lexer->curChar;
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    token = create_token(str, SLASH);
  } else if (lexer->curChar == '*') {
    char ch = lexer->curChar;
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    token = create_token(str, ASTERISK);
  } else if (lexer->curChar == '\n') {
    char ch = lexer->curChar;
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    token = create_token(str, NEWLINE);
  } else if (lexer->curChar == '\0') {
    char ch = lexer->curChar;
    char str[2];
    str[0] = ch;
    str[1] = '\0';
    token = create_token(str, EOF_TOKEN);
  } else if (lexer->curChar == '=') {
    if (lexer->peek(lexer) == '=') {
      char result[2];
      result[0] = lexer->curChar;
      lexer->nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, EQEQ);
    } else {
      char ch = lexer->curChar;
      char str[2];
      str[0] = ch;
      str[1] = '\0';
      token = create_token(str, EQ);
    }
  } else if (lexer->curChar == '<') {
    if (lexer->peek(lexer) == '=') {
      char result[2];
      result[0] = lexer->curChar;
      lexer->nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, LTEQ);
    } else {
      char ch = lexer->curChar;
      char str[2];
      str[0] = ch;
      str[1] = '\0';
      token = create_token(str, LT);
    }
  } else if (lexer->curChar == '>') {
    if (lexer->peek(lexer) == '=') {
      char result[2];
      result[0] = lexer->curChar;
      lexer->nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, GTEQ);
    } else {
      char ch = lexer->curChar;
      char str[2];
      str[0] = ch;
      str[1] = '\0';
      token = create_token(str, GT);
    }
  } else if (lexer->curChar == '!') {
    if (lexer->peek(lexer) == '=') {
      char result[2];
      result[0] = lexer->curChar;
      lexer->nextChar(lexer);
      result[1] = lexer->curChar;
      token = create_token(result, NOTEQ);
    } else {
      lexer->abort_lex(lexer);
    }
  } else if (lexer->curChar == '\"') {
    lexer->nextChar(lexer);
    int index = 0;
    int capacity = 10;
    char *stringValue = (char *)malloc(capacity * sizeof(char));

    while (lexer->curChar != '\"') {
      if (lexer->curChar == '\r' || lexer->curChar == '\t' ||
          lexer->curChar == '\n') {
        lexer->abort_lex(lexer);
      }
      if (index >= capacity - 1) {
        capacity = capacity * 2;
        char *temp = realloc(stringValue, capacity * sizeof(char));
        stringValue = temp;
      }
      printf("%c\n", lexer->curChar);
      lexer->nextChar(lexer);
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
  }
  lexer->nextChar(lexer);
  return token;
}
