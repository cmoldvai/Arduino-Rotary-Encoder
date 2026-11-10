# Arduino Rotary Encoder

This project contains Arduino firmware for testing the Propwash dual quadrature rotary encoder with pushbutton. The firmware reads both encoders and the pushbutton, then prints their events to the serial port. It is configured for an ATmega328P-based Adafruit Metro.

## Hardware and wiring

The sketch uses the board's internal pull-up resistors. Connect each encoder's
common pin and the button's common pin to GND.

| Signal                     | Board pin |
| -------------------------- | --------- |
| Inner encoder A            | D4        |
| Inner encoder B            | D5        |
| Outer encoder A            | D3        |
| Outer encoder B            | D2        |
| Push button                | D6        |
| Encoder and button commons | GND       |

## Build, upload, and monitor

Install [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html)
or the PlatformIO IDE extension for VS Code, then run these commands from the
project directory:

```sh
pio run
pio run --target upload
pio device monitor --baud 115200
```

The project is configured for the `metro` board environment. If PlatformIO
doesn't automatically detect your board's serial port, specify it for upload:

```sh
pio run --target upload --upload-port COM6
```

Replace `COM6` with the port used by your board. The serial monitor should
print `DUAL_ROTARY_ENCODER,READY` after startup, followed by events such as:

```text
SMALL KNOB,CW
LARGE KNOB,CCW
BUTTON,PRESSED
BUTTON,RELEASED
```

If an encoder's direction is reversed, swap its A and B wires. If a detent
produces no event or multiple events, adjust `ENCODER_STEPS_PER_DETENT` in
[`src/main.cpp`](src/main.cpp) to match the encoder.

This is a hardware test sketch; it is not Air Manager Knobster firmware.
