#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

typedef enum lexerState {Nothing, AnInteger, ALeftParen, ARightParen} LexerState;

int currentInteger = 0;
int currentlyLexing = Nothing;

Token lex(char c) {
  if(currentlyLexing == Nothing) {
    if(isdigit(c)) {
      currentlyLexing = AnInteger;
    }
    if(c == '(') { 
      currentlyLexing = ALeftParen;
    }
    if(c == ')') { 
      currentlyLexing = ARightParen;
    }
  }

  Token t;
  
  if(currentlyLexing == AnInteger) { 
    if(isspace(c)) {
      t.type = Integer;
      t.val.integer = currentInteger;
      currentInteger = 0;
      currentlyLexing = Nothing;
    } else { 
      currentlyLexing = AnInteger;
      currentInteger = currentInteger * 10;
      currentInteger = currentInteger + (c - '0');
      t.type = Nothing;
    }
    return t;
  }
  
  if(currentlyLexing == ALeftParen) { 
    t.type = LeftParen;
    currentlyLexing = Nothing;
    return t;
  }
  
  if(currentlyLexing == ARightParen) { 
    t.type = RightParen;
    currentlyLexing = Nothing;
    return t;
  }

  t.type = Empty;
  return t;
}
