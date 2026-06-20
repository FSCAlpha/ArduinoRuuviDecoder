#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

uint8_t hex_char_to_byte(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

bool check_hex_string(char *str) {
    for (int c = 0; c < strlen(str); c++) {
        if (!isxdigit(str[c])) {
            return false;
        }
    }
    return true;
}

bool hex_to_bytes(char *hex_str, uint8_t* out) {
    char *ptr = hex_str;

    // Skip 0x (guard against reading past a 1-char string)
    if (hex_str[0] == '0' && hex_str[1] == 'x') {
        ptr += 2;
    }

    // Must be exactly 24 bytes worth of hex digits, or the loop below
    // would read past the end of the string.
    if (strlen(ptr) != 48) return false;
    if (!check_hex_string(ptr)) return false;

    for (int i = 0; i < 24; i++) {
        out[i] = (hex_char_to_byte(ptr[i*2]) << 4) | hex_char_to_byte(ptr[i*2+1]);
    }

    return true;
}
