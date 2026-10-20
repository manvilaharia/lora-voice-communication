# Long-Range Wireless Voice Communication Using LoRa

A long-range wireless communication prototype built using two ESP32 boards and SX1278 LoRa modules operating at 433 MHz. The project explores communication in rural areas, disaster zones and remote locations where cellular networks or internet connectivity may be unavailable.

## Overview

LoRa uses Chirp Spread Spectrum modulation to support long-range wireless communication at low data rates and low power consumption. This project uses ESP32 microcontrollers and SX1278 transceivers to establish a wireless link between a transmitter and receiver.

The current prototype demonstrates the transmission of button status and microphone readings. Actual audio streaming and playback are planned future extensions.

## Objectives

- Develop a low-cost wireless communication prototype using LoRa.
- Transmit microphone readings and control information between two ESP32 boards.
- Receive transmitted packets and indicate button status using an LED.
- Explore the potential for long-range communication without cellular or internet connectivity.

## Hardware

- Two ESP32 development boards
- Two SX1278 LoRa modules
- MAX9814 microphone module
- Push button
- LED and resistors
- Breadboard and jumper wires

## System Design
<img width="895" height="500" alt="image" src="https://github.com/user-attachments/assets/8c4de244-58a6-4ab4-a614-964d1bc67064" />


### Transmitter

The transmitter reads the microphone's analog output through the ESP32 ADC and monitors the push button. When the button is pressed and the microphone reading exceeds a configured threshold, the transmitter sends a `BTN ON` message and the microphone reading. Otherwise, it sends a `BTN OFF` message and the reading.

The ESP32 communicates with the LoRa module through SPI, and the SX1278 transmits the packet wirelessly.

### Receiver

The receiver listens for incoming LoRa packets and reads their contents. It checks the button status and switches the LED accordingly. The receiver also extracts the transmitted microphone reading and displays it through the Serial Monitor.

The current implementation does not reconstruct audio or play it through a speaker.

## Pin Connections

| Signal | ESP32 GPIO |
|---|---|
| LoRa CS / NSS | 5 |
| LoRa Reset | 14 |
| LoRa DIO0 | 2 |
| LoRa MOSI | 23 |
| LoRa MISO | 19 |
| LoRa SCK | 18 |
| Microphone analog output | 32 |
| Push button in transmitter code | 35 |
| Status LED in receiver code | 22 |

The presentation schematic shows the push button connected to GPIO 33, while the transmitter code uses GPIO 35. On a classic ESP32, GPIO 35 is input-only and does not support an internal pull-up. The wiring and code should be reconciled before hardware deployment. An external pull-up or a suitable GPIO supporting internal pull-ups is required.

## Software

Both transmitter and receiver sketches use the Arduino framework and the [LoRa library by Sandeep Mistry](https://github.com/sandeepmistry/arduino-LoRa).

1. Install the Arduino IDE and ESP32 board support.
2. Install the LoRa library through the Arduino Library Manager.
3. Upload `transmitter/transmitter.ino` to the transmitter ESP32.
4. Upload `receiver/receiver.ino` to the receiver ESP32.
5. Open the Serial Monitor at 9600 baud to observe transmitted and received messages.
6. Adjust the microphone threshold based on observed ADC readings if required.

## Current Implementation

The transmitter sends button status and microphone ADC readings as LoRa packets. The receiver parses the packets, extracts the microphone reading and controls an LED according to the received button status.

This demonstrates basic packet transmission and reception over the LoRa link. Continuous voice transmission, audio decoding and speaker playback have not been implemented in the current code.

## Results

The project presentation documents the hardware prototype and its communication workflow. The implemented code provides a mechanism for transmitting button status and microphone readings to the receiver.

Actual audio quality and communication range should be measured separately before making claims about voice quality or kilometer-scale performance.
<img width="457" height="256" alt="image" src="https://github.com/user-attachments/assets/b396cc7d-b117-480e-bfcb-8793e0f0e1d6" />
<img width="452" height="251" alt="image" src="https://github.com/user-attachments/assets/ac5a6d0f-c760-41c1-bbd5-c4a85ece0e64" />



## Applications

- Emergency communication during network outages
- Rural and remote connectivity
- Rescue and field operations
- Industrial and mining environments
- Outdoor expeditions

## Future Work

- Transmit sampled audio data rather than individual microphone readings
- Explore audio encoding and compression
- Reconstruct audio using a DAC, amplifier and speaker
- Develop two-way communication
- Measure communication range, latency and reliability under different LoRa settings
