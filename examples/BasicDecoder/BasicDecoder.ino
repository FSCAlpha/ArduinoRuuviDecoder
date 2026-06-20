
#include <RuuviTagDecoder.h>

// Official RuuviTag Data Format 5 (RAWv2) test vector.
// https://docs.ruuvi.com/communication/bluetooth-advertisements/data-format-5-rawv2#test-vectors
uint8_t sampleData[] = {
    0x05,        // Format (5 = RAWv2)
    0x12, 0xFC,  // Temperature (+24.3°C)
    0x53, 0x94,  // Humidity (53.49%)
    0xC3, 0x7C,  // Pressure (1000.44 hPa)
    0x00, 0x04,  // Acceleration X (+0.004 G)
    0xFF, 0xFC,  // Acceleration Y (-0.004 G)
    0x04, 0x0C,  // Acceleration Z (+1.036 G)
    0xAC, 0x36,  // Battery (2.977V), TX Power (+4dBm)
    0x42,        // Movement counter (66)
    0x00, 0xCD,  // Measurement sequence (205)
    0xCB, 0xB8, 0x33, 0x4C, 0x88, 0x4F  // MAC address (CB:B8:33:4C:88:4F)
};

RuuviTagDecoder decoder;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("RuuviTag Decoder - Basic Example");
    Serial.println("=================================\n");

    // Decode the sample data
    if (decoder.decode(sampleData, sizeof(sampleData))) {
        Serial.println("Successfully decoded RuuviTag data!\n");

        Serial.print("Temperature: ");
        Serial.print(decoder.getTemp());
        Serial.println(" °C");

        Serial.print("Temperature: ");
        Serial.print(decoder.getTempF());
        Serial.println(" °F");

        Serial.print("Humidity: ");
        Serial.print(decoder.getHumidity());
        Serial.println(" %");

        Serial.print("Pressure: ");
        Serial.print(decoder.getPressure());
        Serial.println(" hPa");

        Serial.print("Battery: ");
        Serial.print(decoder.getBatteryVoltage() / 1000.0f);  // getBatteryVoltage() returns mV
        Serial.println(" V");

    } else {
        Serial.println("Failed to decode data!");
    }
}

void loop() {
    while(1);
}
