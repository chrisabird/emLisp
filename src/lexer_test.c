#include "lexer_test.h"

bool should_lex_empty_as_empty() { 
  Token t = findNextToken();
  return assertIntegerEquals(t.type, Empty);
}

bool should_lex_space_char_as_empty() {
  handleChar(' ');
  Token t = findNextToken();
  return assertIntegerEquals(t.type, Empty);
}

bool should_lex_left_paren_as_token() { 
  handleChar('(');
  Token t = findNextToken();
  return assertIntegerEquals(t.type, LeftParen);
}


bool should_lex_right_paren_as_token() { 
  handleChar(')');
  Token t = findNextToken();
  return assertIntegerEquals(t.type, RightParen);
}

bool should_lex_integer_as_token() {
  handleChar('0');
  handleChar(' ');
  Token t = findNextToken();
  return assertIntegerEquals(t.type, Integer);
}

bool should_lex_integer_as_token_with_value() {
  handleChar('1');
  handleChar(' ');
  Token t = findNextToken();
  return assertIntegerEquals(t.val.integer, 1);
}

bool should_lex_multi_digit_integer_as_token_with_value() {
  handleChar('1');
  handleChar('0');
  handleChar(' ');
  Token t = findNextToken();
  return assertIntegerEquals(t.val.integer, 10);
}

bool should_lex_integer_terminated_with_non_space_charater() { 
  handleChar('1');
  handleChar('0');
  Token t = findNextToken();
  return assertIntegerEquals(t.val.integer, 10);
}

bool should_lex_char() { 
  handleChar('\'');
  handleChar('c');
  handleChar('\'');
  Token t = findNextToken();
  return assertCharEquals(t.val.character, 'c');
}

bool should_lex_symbol_as_token() {
  handleChar('a');
  Token t = findNextToken();
  return assertIntegerEquals(t.type, Symbol);
}

bool should_lex_symbol_as_token_with_value() {
  handleChar('a');
  handleChar('b');
  handleChar('c');
  Token t = findNextToken();
  return assertCharEquals(t.val.symbol[0], 'a') && assertCharEquals(t.val.symbol[1], 'b') && assertCharEquals(t.val.symbol[2], 'c');
}

bool test_lexer() {
  init();

  test(should_lex_empty_as_empty, "should empty as empty token");
  test(should_lex_space_char_as_empty, "should lex space char as empty token");
  test(should_lex_left_paren_as_token, "should lex left paren as token");
  test(should_lex_right_paren_as_token, "should lex right paren as token");
  test(should_lex_integer_as_token, "should lex integer as token");
  test(should_lex_integer_as_token_with_value, "should lex single integer as token with value");
  test(should_lex_multi_digit_integer_as_token_with_value, "should lex single integer as token with value");
  test(should_lex_integer_terminated_with_non_space_charater, "should lex integer terminated with non space character");
  test(should_lex_char, "should lex char");
  test(should_lex_symbol_as_token, "should lex symbol");
  test(should_lex_symbol_as_token_with_value, "should lex symbol with value");
  return true;
}
