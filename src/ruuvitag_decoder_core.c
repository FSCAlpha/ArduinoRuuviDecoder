#include "ruuvitag_decoder_core.h"
#include <string.h>
#include <stdio.h>

bool ruuvi_decode_format5(const uint8_t* raw_data, uint8_t data_len, ruuvi_data_t* output) {
    output->valid = false;

    // Not format 5
    if (raw_data[0] != 5) {
        return false;
    }

    int16_t temp_raw = (int16_t)((raw_data[1] << 8) | raw_data[2]);
    if (temp_raw == (int16_t)0x8000) {
        return false;  // Invalid temperature
    }

    uint16_t humidity_raw = (uint16_t)((raw_data[3] << 8) | raw_data[4]);
    if (humidity_raw == 0xFFFF) {
        return false;  // Invalid humidity
    }

    uint16_t pressure_raw = (uint16_t)((raw_data[5] << 8) | raw_data[6]);
    if (pressure_raw == 0xFFFF) {
        return false;  // Invalid pressure
    }

    int16_t accel_x_raw = (int16_t)((raw_data[7] << 8) | raw_data[8]);
    int16_t accel_y_raw = (int16_t)((raw_data[9] << 8) | raw_data[10]);
    int16_t accel_z_raw = (int16_t)((raw_data[11] << 8) | raw_data[12]);
    if (accel_x_raw == (int16_t)0x8000 ||
        accel_y_raw == (int16_t)0x8000 ||
        accel_z_raw == (int16_t)0x8000) {
        return false;  // Invalid acceleration
    }

    uint16_t battery_raw = (uint16_t)((raw_data[13] << 8 | (raw_data[14] & 0xE0)) >> 5);
    if (battery_raw == 0x7FF) {
        return false;  // Invalid battery voltage
    }

    uint8_t tx_power_raw = (raw_data[14] & 0x1F);
    if (tx_power_raw == 0x1F) {
        return false;  // Invalid TX power
    }

    if (raw_data[15] == 0xFF) {
        return false;  // Invalid movement counter
    }

    uint16_t sequence_raw = (uint16_t)(raw_data[16] << 8 | raw_data[17]);
    if (sequence_raw == 0xFFFF) {
        return false;  // Invalid measurement sequence
    }

    output->format = 5;
    output->temperature = temp_raw * 0.005f;
    output->humidity = humidity_raw * 0.0025f;
    output->pressure = (uint32_t)(pressure_raw + 50000);
    output->accel_x = accel_x_raw * 0.001f;
    output->accel_y = accel_y_raw * 0.001f;
    output->accel_z = accel_z_raw * 0.001f;
    output->battery_voltage = battery_raw + 1600;
    output->tx_power = (int8_t)(-40 + (tx_power_raw * 2));
    output->movement_counter = raw_data[15];
    output->measurement_sequence = sequence_raw;
    memcpy(output->mac, &raw_data[18], 6);

    output->valid = true;
    return true;
}
