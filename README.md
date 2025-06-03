# Lqy-Project: A switch light system based on voice recognition and Bluetooth control
(Design Thinking for Microcontroller Systems)
## Mbed Version
Mbed 5.15 is used in this project
## Abstract
This project presents an integrated embedded systems course design utilizing the ARM Cortex-M4 based MBED L432KC development board. The system incorporates:
- Wireless communication via UART Bluetooth (BT24 module)
- Visual output through I²C-interfaced OLED (SH1106 controller, 128×64 resolution)
- Audio pattern recognition using SU03T voice recognition IC
- Real-time debugging via online serial port monitoring

## Hardware Architecture
```mermaid
graph TD
    A[MBED L432KC] --> B[HC-05 Bluetooth]
    A --> C[SH1106 OLED]
    A --> D[SU03T Voice Module]
    A --> E[Servo Motors]
    A --> F[Debug Interface]
