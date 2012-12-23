#include "cunit.h"

void test(bool (*testFunc)(), char *testName) {
 if(!(*testFunc)()){
  printf("FAIL: %s\r\n", testName);
 }
}

bool assertCharEquals(char value, char expected) { 
  if(value != expected) { 
    printf("Expected '%c' but got '%c'\r\n", expected, value);
    return false;
  }
  return true;
}

bool assertIntegerEquals(int value, int expected) { 
  if(value != expected) { 
    printf("Expected '%d' but got '%d'\r\n", expected, value);
    return false;
  }
  return true;
}
