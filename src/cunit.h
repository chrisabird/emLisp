#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void test(bool (*testFunc)(), char *testName);

bool assertCharEquals(char value, char expected);
bool assertIntegerEquals(int value, int expected);
