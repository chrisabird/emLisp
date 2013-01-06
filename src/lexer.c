#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// TODO: Handle characters that need escaping 

typedef enum lexerState {Nothing, AnInteger, ACharacter, ASymbol} LexerState;

char *buffer;
int bufferWritePosition = 0;
int bufferReadPosition = 0;

void init() { 
  buffer = malloc(128 * sizeof(char));
}

void handleChar(char c) { 
  buffer[bufferWritePosition++] = c;
}

int isNul(char c) {
  return c == 0;
}

int isSingleQuote(char c) { 
  return c == '\'';
}

int isOpenParen(char c) {
  return c == '(';
}

int isCloseParen(char c) {
  return c == ')';
}

Token leftParen() {
  Token t = {.type = LeftParen};
  return t;
}

Token rightParen() { 
  Token t = {.type = RightParen};
  return t;
}

Token integer(int currentValue) { 
  Token t = {.type = Integer, .val.integer = currentValue };
  return t;
}

Token character(char currentValue) {
  Token t = {.type = Character, .val.character = currentValue };
  return t;
}

Token symbol(char *currentSymbol) {
  Token t = {.type = Symbol};
  memcpy(t.val.symbol, currentSymbol, 7 * sizeof(char));
  return t;
}

Token empty() {
  Token t = {.type = Empty };
  return t;
}

Token findNextToken() {
  int currentlyLexing = Nothing;
  int currentValue = 0;
  int currentSymbolCharacter = 0;
  char currentSymbol[7];

  while(bufferReadPosition < bufferWritePosition) {
    char c = buffer[bufferReadPosition++];
    char la = 0;
    if(bufferReadPosition < bufferWritePosition) {
      la = buffer[bufferReadPosition];
    }

    if(currentlyLexing == Nothing) {
      if(isspace(c)) { 
        continue;
      }
      else if(isdigit(c)) {
        currentValue = 0;
        currentlyLexing = AnInteger;
      }
      else if(isSingleQuote(c)) {
        currentValue = 0;
        currentlyLexing = ACharacter;
        continue;
      }
      else if(isOpenParen(c)) {
        return leftParen();
      }
      else if(isCloseParen(c)) {
        return rightParen();
      }
      else if(isgraph(c)) { 
        currentlyLexing = ASymbol;
      }
    }

    if(currentlyLexing == AnInteger) {
        currentValue = currentValue * 10;
        currentValue = currentValue + (c - '0');

      if(isNul(la) || !isdigit(la)) { 
        currentlyLexing = Nothing;
        return integer(currentValue);
      }
    }

    if(currentlyLexing == ACharacter) {
      if (isSingleQuote(c)) {
        return character(currentValue);
      } else { 
        currentValue = c;
      }
    }

    if(currentlyLexing == ASymbol) {
      currentSymbol[currentSymbolCharacter++] = c;

      if(isNul(la) || isOpenParen(c) || isCloseParen(c) || isspace(c)) {
        return symbol(currentSymbol); 
      }
    }
  }
  return empty();
}
