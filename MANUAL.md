# Manual

## Physical Interface

### Inputs

- Rotary encoder with push button
- Reset button

### Outputs

- Status LED
- Output light (LED in prototype)

### Usage

#### Controllng the output light

Adjust brightness of the output light with the rotary encoder. Turn clockwise to increase brightness, turn anticlockwise to decrease brightness.

Turn output light on/off without changing the brightness, with the rotary encoder push button.

Decreasing brightness to zero will turn the output light off but set the brightness to max (so that if you turn it on with the push button it will come on fully, instead of with brightness zero).

Increasing the brightness from off will turn the output light on and increment from the lowest brightness.

#### Reset button functions

- Press to reboot the device
- Press and hold for 2 seconds to query the current network status
  - The status LED will flash once and after the button is released it will flash the following additional times
    - 1 - Connected to configured WiFi network
    - 2 - Access point started
    - 4 - Off
- Press and hold for 5 seconds to toggle the Access Point network mode
  - The status LED will flash twice
- Press and hold for 10 seconds to start WPS Config network mode
  - The status LED will flash 3 times
- Press and hold for 20 seconds to toggle the WiFi on/off
  - The status LED will flash 4 times
- Press and hold for 30 seconds to restore factory settings
  - The status LED will flash 5 times

## Network modes

### Normal

#### If no WiFi network is configured

If no WiFi network is configured then it will start the configured Access Point. On first start this will be the default behaviour as no WiFi network will be configured and the default factory Access Point settings will be used.

#### If the WiFi network settings have been set

The device will connect to the configured WiFi network.

If the device fails to connect to the configured WiFi network then it will start an Access Point, with the configured settings, after the configured timeout (if enabled).

### Access Point

The device will not connect to any configured WiFi network but will instead start an Access Point with its configured settings.

When the Access Point is toggled off it will return to Normal mode.

The Access Point can be configured to timeout after a fixed period. When this happens it will return to the previous mode (either Off or Normal).

The Access Point can also be configured to not timeout if there are clients connected (the timer will restart when the last client disconnects).

### WPS Config

The device will attempt to retrieve WiFi configuration using WPS. After starting this mode it is ncessary to press the WPS button on the Access Point you wish to connect to.

Once the configuration has been retrieved it will be applied and the device will change to Normal mode.

If the WPS Config mode times out (after N seconds) the device will return to the previous mode (one of Normal, Access Point or Off).

**NB. WPS Config mode blocks the operation of the device, so it will not be possible to do anything else with it until it completes or times out.**

### Off

The WiFi will be disconnected and no Access Point will be started.

When the WiFi is turned back on it will return to the previous mode (either Normal or Access Point)

**NB. When the WiFi is off, the device will not be able to communicate with any other device and as such will revert to its default behaviour of only controlling its own output light.**

## Configuration portal

## API
