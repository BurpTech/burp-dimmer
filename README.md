# burp-dimmer

**IN DEVELOPMENT**

ESP8266 smart dimmer implementation

**NB. Clone recursively to get submodules**

**NB. A note on my `Wemos D1 mini pro` board**

My Wemos board seems to not be to spec as it only has 4MB flash memory instead of 16MB. As such I program it as a `d1_mini` platformio. If your board is to the correct spec then you may be able to use the `d1_mini_pro` option.

## Components

![breadboard](breadboard.jpeg)

- Wemos D1 mini pro* (see note)
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

### Prequisites

Connect the Wemos board to your computer with the micro USB cable.

This is the PlatformIO version currently being used:

- PlatformIO Core 4.3.4 - https://docs.platformio.org/en/latest/core/installation.html

### Flashing the SPIFFS file system

The `sketch/data` directory contains files that are required at run time and need to be flashed onto the board.

**NB. Doing this will remove any existing files (eg. modified config files)**

```
platformio run -t uploadfs
```

### Flashing the firmware

```
platformio run -t upload
```

## Listening to the serial output

```
platformio device monitor
```

Stop the monitor using `CTRL-C`

## Erasing the flash file system

**NB. this will remove the program, file system and any data stored in EEPROM (ie. the factory settings will reinitialize)**

```
platformio run -t erase
```
