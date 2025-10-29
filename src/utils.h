#ifndef RUUVI_TAG_DECODER_UTILS
#define RUUVI_TAG_DECODER_UTILS

#include <stdbool.h>
#include <stdint.h>

// Converts a hex string (eg. 0xABC123) to raw bytes.
// Returns true on success, else false
bool hex_to_bytes(char *hex_str, uint8_t *out);

// Helper function for hex_to_bytes
uint8_t hex_char_to_byte(char c);

// Check if hex string is valid hexadecimal
// Returns true on success, else false
bool check_hex_string(char *str);

#endif // RUUVI_TAG_DECODER_UTILS