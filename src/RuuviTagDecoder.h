#ifndef RUUVI_TAG_DECODER_H
#define RUUVI_TAG_DECODER_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdio>
#endif

#include "ruuvitag_decoder_core.h"
#include <string.h>

/**
 * Arduino-friendly C++ wrapper for RuuviTag decoder
 *
 * Usage:
 *   RuuviTagDecoder decoder;
 *   if (decoder.decode(rawData, dataLen)) {
 *       float temp = decoder.getTemp();
 *       float humidity = decoder.getHumidity();
 *   }
 */
class RuuviTagDecoder {
private:
    ruuvi_data_t data;

public:
    RuuviTagDecoder() {
        memset(&data, 0, sizeof(ruuvi_data_t));
    }

    /**
     * Decode RuuviTag data
     * @param rawData Pointer to manufacturer data
     * @param dataLen Length of data
     * @return true if decode successful
     */
    bool decode(const uint8_t* rawData, uint8_t dataLen) {
        return ruuvi_decode_format5(rawData, dataLen, &data);
    }

    /**
     * Decode RuuviTag Format 5 (RAWv2) data
     * @param rawData Pointer to manufacturer data
     * @param dataLen Length of data
     * @return true if decode successful
     */
    bool decodeFormat5(const uint8_t* rawData, uint8_t dataLen) {
        return ruuvi_decode_format5(rawData, dataLen, &data);
    }

    /** Get temperature in Celsius */
    float getTemp() const { return data.temperature; }

    /** Get temperature in Celsius (alias) */
    float getTemperature() const { return data.temperature; }

    /** Get temperature in Fahrenheit */
    float getTempF() const { return data.temperature * 9.0f / 5.0f + 32.0f; }

    /** Get humidity in % */
    float getHumidity() const { return data.humidity; }

    /** Get pressure in hPa */
    float getPressure() const { return data.pressure / 100.0f; }
    
    /** Get pressure in Pa */
    float getPressureRaw() const { return data.pressure; }

    /** Get acceleration X in G */
    float getAccelX() const { return data.accel_x; }

    /** Get acceleration Y in G */
    float getAccelY() const { return data.accel_y; }

    /** Get acceleration Z in G */
    float getAccelZ() const { return data.accel_z; }

    /** Get battery voltage in millivolts */
    float getBatteryVoltage() const { return data.battery_voltage; }

    /** Get TX power in dBm */
    int8_t getTxPower() const { return data.tx_power; }

    /** Get movement counter */
    uint8_t getMovementCounter() const { return data.movement_counter; }

    /** Get measurement sequence number */
    uint16_t getMeasurementSequence() const { return data.measurement_sequence; }

    /** Get MAC address (6 bytes) */
    const uint8_t* getMac() const { return data.mac; }

    /** Check if last decode was valid */
    bool isValid() const { return data.valid; }

    /**
     * Get MAC address as a formatted string
     * @param buffer Buffer to write MAC string to (min 18 bytes)
     */
    void getMacString(char* buffer) const {
        sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X",
                data.mac[0], data.mac[1], data.mac[2],
                data.mac[3], data.mac[4], data.mac[5]);
    }
};

#endif // RUUVI_TAG_DECODER_H
