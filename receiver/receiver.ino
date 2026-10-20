
#include <SPI.h>
#include <LoRa.h>

#define LED_PIN 22
#define LORA_CS 5
#define LORA_RST 14
#define LORA_DIO0 2

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);

    LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa init failed. Check connections.");
        while (true);
    }

    Serial.println("LoRa Receiver Initialized");
}

void loop() {
    int packetSize = LoRa.parsePacket();

    if (packetSize) {
        String rxMsg = "";

        while (LoRa.available()) {
            rxMsg += (char)LoRa.read();
        }

        rxMsg.trim();

        Serial.print("Received: ");
        Serial.println(rxMsg);

        if (rxMsg.startsWith("BTN ON")) {
            digitalWrite(LED_PIN, HIGH);
        } else if (rxMsg.startsWith("BTN OFF")) {
            digitalWrite(LED_PIN, LOW);
        }

        int commaIndex = rxMsg.indexOf(',');

        if (commaIndex > 0) {
            int micValue = rxMsg.substring(commaIndex + 1).toInt();

            Serial.print("Mic Value: ");
            Serial.println(micValue);
        }
    }
}
