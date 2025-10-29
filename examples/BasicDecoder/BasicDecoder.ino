
#include <RuuviTagDecoder.h>

uint8_t sampleData[] = {
    0x05,        // Format (5 = RAWv2)
    0x12, 0xFC,  // Temperature (+24.3°C)
    0xC3, 0x74,  // Humidity (53.49%)
    0x00, 0xD7,  // Pressure (1000.15 hPa)
    0x03, 0xE8,  // Acceleration X (+1.000 G)
    0x00, 0x00,  // Acceleration Y (0.000 G)
    0x04, 0x00,  // Acceleration Z (+1.024 G)
    0x0B, 0xAC,  // Battery (2.977V), TX Power (+4dBm)
    0x64,        // Movement counter (100)
    0x00, 0x04,  // Measurement sequence (4)
    0xC3, 0x6E, 0xF8, 0x12, 0xAC, 0x5E  // MAC address
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
        Serial.print(decoder.getBatteryVoltage());
        Serial.println(" V");

    } else {
        Serial.println("Failed to decode data!");
    }
}

void loop() {
    while(1);
}
