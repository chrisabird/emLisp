#include "lexer_test.h"


bool should_lex_space_char_as_empty() {
  Token t = lex(' ');
  return assertIntegerEquals(t.type, Empty);
}

bool should_lex_left_paren_as_token() { 
  Token t = lex('(');
  return assertIntegerEquals(t.type, LeftParen);
}


bool should_lex_right_paren_as_token() { 
  Token t = lex(')');
  return assertIntegerEquals(t.type, RightParen);
}

bool should_lex_integer_as_token() {
  Token t = lex('0');
  t = lex(' ');
  return assertIntegerEquals(t.type, Integer);
}

bool should_lex_integer_as_token_with_value() {
  Token t = lex('1');
  t = lex(' ');
  return assertIntegerEquals(t.val.integer, 1);
}

bool should_lex_multi_digit_integer_as_token_with_value() {
  Token t = lex('1');
  t = lex('0');
  t = lex(' ');
  return assertIntegerEquals(t.val.integer, 10);
}

bool should_lex_integer_terminated_with_non_space_charater() { 
  return false;
}

bool test_lexer() {
   test(should_lex_space_char_as_empty, "should lex space char as empty token");
   test(should_lex_left_paren_as_token, "should lex left paren as token");
   test(should_lex_right_paren_as_token, "should lex right paren as token");
   test(should_lex_integer_as_token, "should lex integer as token");
   test(should_lex_integer_as_token_with_value, "should lex single integer as token with value");
   test(should_lex_multi_digit_integer_as_token_with_value, "should lex single integer as token with value");
   test(should_lex_integer_terminated_with_non_space_charater, "should lex integer terminated with non space character");
   return true;
}
