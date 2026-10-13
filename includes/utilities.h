#ifndef UTILITIES_H
#define UTILITIES_H

#include "libs.h"
#include "BigNumber.h"

bool is_valid_number(char *number);
bool are_equal_in_length(char *Number1, char *Number2);
int max(int number1, int number2);
int min(int number1, int number2);
void print_number(struct BigNumber *num);

#endif
