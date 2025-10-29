#ifndef RUUVITAG_DECODER_CORE_H
#define RUUVITAG_DECODER_CORE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t format;             // Data format version
    float temperature;          // Temperature in Celsius
    float humidity;             // Humidity in %
    uint32_t pressure;          // Pressure in Pa
    float accel_x;              // Acceleration X in G
    float accel_y;              // Acceleration Y in G
    float accel_z;              // Acceleration Z in G
    uint16_t battery_voltage;   // Battery voltage in mV
    int8_t tx_power;            // TX power in dBm
    uint8_t movement_counter;
    uint16_t measurement_sequence;
    uint8_t mac[6];             // MAC address
    bool valid;                 // Is decode valid
} ruuvi_data_t;

/**
 * Decode RuuviTag RAWv2 (Data Format 5) data
 * @param raw_data Pointer to 24-byte manufacturer data
 * @param data_len Length of raw_data (should be 24)
 * @param output Pointer to output structure
 * @return true if successful, false otherwise
 */
bool ruuvi_decode_format5(const uint8_t* raw_data, uint8_t data_len, ruuvi_data_t* output);

#ifdef __cplusplus
}
#endif

#endif // RUUVITAG_DECODER_CORE_H
