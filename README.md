# smart-dimmer

**IN DEVELOPMENT**

Arduino ESP8266 smart dimmer implementation

## Components

![breadboard](breadboard.jpeg)

- Wemos D1 mini pro* (mine seem to have the wrong size flash at 4MB instead of 16MB!)
- KY-040 Rotary Encoder (with push button)
- LED
- 220 ohm resistor
- Momentary switch
- Micro USB cable
- Breadboard and jumper cables :)

## Wiring

![breadboard wiring](breadboard_bb.png)

Rotary encoder pins should be connected to the Wemos as follows:

- CLK (Pin A) -> D5 (Orange)
- DT (Pin B) -> D6 (Blue)
- SW (switch) -> D7 (Green)
