#include "../utils.h"
#include "../ruuvitag_decoder_core.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// See https://docs.ruuvi.com/communication/bluetooth-advertisements/data-format-5-rawv2#test-vectors
uint8_t vector_valid[] = {
    0x05, 0x12, 0xFC, 0x53, 0x94, 0xC3, 0x7C, 0x00,
    0x04, 0xFF, 0xFC, 0x04, 0x0C, 0xAC, 0x36, 0x42,
    0x00, 0xCD, 0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F
};

char *vector_valid_str = "0x0512FC5394C37C0004FFFC040CAC364200CDCBB8334C884F";

ruuvi_data_t vector_valid_expected = {
    .format = 5,
    .temperature = 24.3f,
    .pressure = 100044,
    .humidity = 53.49f,
    .accel_x = 0.004f,
    .accel_y = -0.004f,
    .accel_z = 1.036f,
    .tx_power = 4,
    .battery_voltage = 2977,
    .movement_counter = 66,
    .measurement_sequence = 205,
    .mac = { 0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F },
    .valid = true
};

TEST(test_valid_string) {
    uint8_t bytes[24] = { 0 };
    ruuvi_data_t decoded;
    ASSERT_TRUE(hex_to_bytes(vector_valid_str, bytes));

    ASSERT_TRUE(ruuvi_decode_format5(bytes, 24, &decoded));
    ASSERT_RUUVI_DATA_EQ(decoded, vector_valid_expected, 0.05f);
}

TEST(test_valid_bytes) {
    ruuvi_data_t decoded;
    ASSERT_TRUE(ruuvi_decode_format5(vector_valid, 24, &decoded));
    ASSERT_RUUVI_DATA_EQ(decoded, vector_valid_expected, 0.05f);
}

char *vector_maximum_str = "0x057FFFFFFEFFFE7FFF7FFF7FFFFFDEFEFFFECBB8334C884F";

uint8_t vector_maximum[] = {
    0x05, 0x7F, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0x7F,
    0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xDE, 0xFE,
    0xFF, 0xFE, 0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F
};

ruuvi_data_t vector_maximum_expected = {
    .format = 5,
    .temperature = 163.835f,
    .humidity = 163.8350f,
    .pressure = 115534,
    .accel_x = 32.767f,
    .accel_y = 32.767f,
    .accel_z = 32.767f,
    .battery_voltage = 3646,
    .tx_power = 20,
    .movement_counter = 254,
    .measurement_sequence = 65534,
    .mac = {0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F},
    .valid = true
};

TEST(test_maximum_string) {
    uint8_t bytes[24] = { 0 };
    ruuvi_data_t decoded;
    ASSERT_TRUE(hex_to_bytes(vector_maximum_str, bytes));

    ASSERT_TRUE(ruuvi_decode_format5(bytes, 24, &decoded));
    ASSERT_RUUVI_DATA_EQ(decoded, vector_maximum_expected, 0.05f);
}

TEST(test_maximum_bytes) {
    ruuvi_data_t decoded;
    ASSERT_TRUE(ruuvi_decode_format5(vector_maximum, 24, &decoded));
    ASSERT_RUUVI_DATA_EQ(decoded, vector_maximum_expected, 0.05f);
}

char *vector_minimum_str = "0x058001000000008001800180010000000000CBB8334C884F";

uint8_t vector_minimum[] = {
    0x05, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x01, 0x80, 0x01, 0x80, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F
};

ruuvi_data_t vector_minimum_expected = {
    .format = 5,
    .temperature = -163.835f,
    .humidity = 0.000f,
    .pressure = 50000,
    .accel_x = -32.767f,
    .accel_y = -32.767f,
    .accel_z = -32.767f,
    .battery_voltage = 1600,
    .tx_power = -40,
    .movement_counter = 0,
    .measurement_sequence = 0,
    .mac = {0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F},
    .valid = true
};

TEST(test_minimum_string) {
    uint8_t bytes[24] = { 0 };
    ruuvi_data_t decoded;
    ASSERT_TRUE(hex_to_bytes(vector_minimum_str, bytes));

    ASSERT_TRUE(ruuvi_decode_format5(bytes, 24, &decoded));
    ASSERT_RUUVI_DATA_EQ(decoded, vector_minimum_expected, 0.05f);
}

TEST(test_minimum_bytes) {
    ruuvi_data_t decoded;
    ASSERT_TRUE(ruuvi_decode_format5(vector_minimum, 24, &decoded));
    ASSERT_RUUVI_DATA_EQ(decoded, vector_minimum_expected, 0.05f);
}

char *vector_invalid_str = "0x058000FFFFFFFF800080008000FFFFFFFFFFFFFFFFFFFFFF";

uint8_t vector_invalid[] = {
    0x05, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x00, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

TEST(test_invalid_string) {
    uint8_t bytes[24] = { 0 };
    ruuvi_data_t decoded;
    ASSERT_TRUE(hex_to_bytes(vector_invalid_str, bytes));

    ASSERT_FALSE(ruuvi_decode_format5(bytes, 24, &decoded));
}

TEST(test_invalid_bytes) {
    ruuvi_data_t decoded;
    ASSERT_FALSE(ruuvi_decode_format5(vector_invalid, 24, &decoded));
}

int main(void) {
    RUN_TEST(test_valid_string);
    RUN_TEST(test_valid_bytes);
    RUN_TEST(test_maximum_string);
    RUN_TEST(test_maximum_bytes);
    RUN_TEST(test_minimum_string);
    RUN_TEST(test_minimum_bytes);
    RUN_TEST(test_invalid_string);
    RUN_TEST(test_invalid_bytes);
    return 0;
}
