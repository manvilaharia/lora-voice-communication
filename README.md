# Long-Range Wireless Voice Communication using LoRa

A long-range, low-power voice communication prototype built with two **ESP32** boards and **LoRa SX1278** (433 MHz) modules. It targets places where cellular networks and the internet are unavailable: rural areas, disaster zones, defense and rescue operations, mining and industrial sites, and outdoor expeditions.

## Overview

LoRa uses Chirp Spread Spectrum (CSS) modulation, giving kilometer-scale range at very low power and strong noise resistance. Wi-Fi and Bluetooth are short-range and power-hungry; LoRa trades data rate (0.3-50 kbit/s per channel) for range.

Key parameters:
- **Spreading Factor (SF 7-12):** higher SF gives longer range but a slower data rate.
- **Bandwidth (BW):** wider BW gives a faster data rate but shorter range.
- **Band used:** 433 MHz (SX1278).

## Objectives

- Build a voice communication system using LoRa that works over long distances where other communication is unavailable.
- Minimize transmission delay so conversations feel natural and real-time.
- Keep the design power-efficient and low-cost for remote, off-grid operation.

## Hardware

- 2x ESP32 development boards
- 2x LoRa SX1278 modules (RA-02)
- MAX9814 microphone module
- Push button
- LEDs and resistors (10k, 330 ohm)
- Breadboard and jumper wires

## System Flow

**Transmitter**
1. Pressing the push button enables the microphone, which converts voice into an analog signal.
2. The ESP32 ADC samples the analog signal into digital values.
3. The ESP32 processes the samples (filtering, optional compression) and packetizes them.
4. Packets go to the LoRa module over SPI.
5. The SX1278 modulates the data using LoRa CSS and transmits it via the antenna.

**Receiver**
1. The antenna captures the signal and the SX1278 demodulates it into data packets.
2. The ESP32 reads packets over SPI (MISO, MOSI, SCK, NSS) using `LoRa.parsePacket()`.
3. The ESP32 reassembles the audio data (with optional decompression, filtering, or error correction).
4. Data is sent to a DAC to convert back to analog (planned extension).
5. A status LED indicates successful reception.

## Pin Connections

| Signal | ESP32 Pin |
|---|---|
| LoRa NSS / CS | 5 |
| LoRa RST | 14 |
| LoRa DIO0 | 2 |
| LoRa MOSI / MISO / SCK | 23 / 19 / 18 (default VSPI) |
| Microphone (analog) | 32 |
| Push button | 35 (transmitter) |
| Status LED | 22 (receiver) |

> **Note:** the schematic in the presentation shows the button wired to GPIO 33, while the code uses GPIO 35. GPIO 35 is input-only and has no internal pull-up, so `INPUT_PULLUP` will not work on it; use an external pull-up (the schematic's 10k resistor) or move the button to a pin that supports internal pull-ups. Make the schematic and code agree before building.

## Software

Both sketches use the Arduino framework with the [arduino-LoRa](https://github.com/sandeepmistry/arduino-LoRa) library.

1. Install the Arduino IDE and add ESP32 board support.
2. Install the **LoRa** library by Sandeep Mistry (Library Manager).
3. Open `transmitter/transmitter.ino` and upload to the transmitter ESP32.
4. Open `receiver/receiver.ino` and upload to the receiver ESP32.
5. Open the Serial Monitor at 9600 baud. Tune `micThreshold` in the transmitter based on the mic values you observe.

## Current Behavior

The prototype sends `BTN ON,<micValue>` when the button is pressed and the mic level exceeds the threshold, otherwise `BTN OFF,<micValue>`. The receiver lights the LED on `BTN ON` and parses the mic value. This validates the LoRa link and the capture/transmit/receive chain; full audio streaming is the next step.

## Results

Voice-activity and mic-level data were transmitted successfully over LoRa and indicated on the receiver LED. See the `docs/` folder for the project presentation and photos.

## Applications

- Emergency communication during disasters and network outages
- Rural and remote connectivity
- Defense, security, and rescue operations
- Industrial and mining areas without Wi-Fi or mobile signal
- Outdoor expeditions (trekking, camping, marine)
- Smart city and IoT integration

## Future Work

- Stream actual audio samples with compression (e.g., ADPCM) over LoRa packets
- Audio reconstruction using a DAC, amplifier, and speaker
- Two-way and group communication
- Range testing across SF/BW settings

\
