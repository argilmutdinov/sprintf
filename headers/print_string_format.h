#pragma once

#include "../headers/power.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_digits_in_different_format(int *counter, unsigned long long number, char format);

unsigned long long converte_to_dec(const char *number, int minus_offset, char format);

void converte_to_format(unsigned long long *decimal_number, char format, char *out_buf, int *i);

int print(char *out_buf, const char *format, const char *number);
