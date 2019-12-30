#include "header.h"

bool is_bit_i_set(unsigned char c, int i) {
    return (1 << i) & c;
}

unsigned char set_bit(unsigned char c, int i) {
    return (1 << i) | c;
}