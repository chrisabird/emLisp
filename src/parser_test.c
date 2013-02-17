#include "parser_test.h"

bool test_lexer() {
  init();

  test(should_lex_empty_as_empty, "should empty as empty token");
  return true;
}
