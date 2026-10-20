# Long-Range Wireless Communication using LoRa

An ESP32-based wireless communication project exploring long-range data transmission using LoRa modules.

## Overview

The project uses ESP32 microcontrollers and SX1278 LoRa transceivers to establish wireless communication between a transmitter and receiver without relying on cellular networks or the internet.

## Hardware

- ESP32 development boards
- SX1278 LoRa modules
- MAX9814 microphone module
- Push button
- LED indicators
- Breadboard and jumper wires

## Transmitter

The transmitter reads the microphone's analog value through the ESP32 ADC and monitors a push button. It sends the button status and microphone reading as LoRa packets using SPI-connected SX1278 hardware.

## Receiver

The receiver listens for incoming LoRa packets, reads the transmitted data and controls an LED according to the received button status.

## Software and Interfaces

- Arduino framework
- SPI communication
- LoRa library
- ESP32 ADC and GPIO

## Current Implementation

The prototype demonstrates LoRa packet transmission, reception and receiver-side status indication using microphone readings and button inputs.

## Future Scope

- Audio encoding and reconstruction
- DAC and amplifier integration
- Speaker output
- Improved audio quality and communication testing
