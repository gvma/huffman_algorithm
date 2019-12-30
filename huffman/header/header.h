#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define DEBUG(x, s) if (x) printf("%s\n", s)

bool is_bit_i_set(unsigned char c, int i);

unsigned char set_bit(unsigned char c, int i);