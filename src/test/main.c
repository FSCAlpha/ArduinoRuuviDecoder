#include "src/utils.h"
#include "src/ruuvitag_decoder_core.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t bytes[24] = { 0 };
    bool valid = hex_to_bytes("0x058000FFFFFFFF800080008000FFFFFFFFFFFFFFFFFFFFFF", bytes);

    if (!valid) {
        printf("Invalid hex string!\n");
        exit(1);
    }
   
    ruuvi_data_t data;
    if (!ruuvi_decode_format5(bytes, 24, &data)) {
        printf("Decode failed!\n");
        exit(1);
    }

    printf("Format: %u\n", data.format);
    printf("Temperature: %.2f°C\n", data.temperature);
    printf("Humidity: %.2f%%\n", data.humidity);
    printf("Pressure: %u Pa\n", data.pressure);
    printf("Acceleration X: %.3f G\n", data.accel_x);
    printf("Acceleration Y: %.3f G\n", data.accel_y);
    printf("Acceleration Z: %.3f G\n", data.accel_z);
    printf("Battery Voltage: %u mV\n", data.battery_voltage);
    printf("TX Power: %d dBm\n", data.tx_power);
    printf("Movement Counter: %u\n", data.movement_counter);
    printf("Measurement Sequence: %u\n", data.measurement_sequence);
    printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
           data.mac[0], data.mac[1], data.mac[2],
           data.mac[3], data.mac[4], data.mac[5]);
    
    return 0;
}
