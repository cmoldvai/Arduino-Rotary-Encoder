# Dual rotary encoder test

This Arduino sketch reads two quadrature rotary encoders and one push button.
It prints events to the Serial Monitor so you can verify the wiring and
direction before using the hardware in another project.

## Wiring

Connect the encoder common pins and the button common pin to GND. The sketch
uses the Arduino's internal pull-up resistors, so no external pull-ups are
needed.

| Signal | Arduino Uno / classic Metro pin |
| --- | --- |
| Inner encoder A | D4 |
| Inner encoder B | D5 |
| Outer encoder A | D3 |
| Outer encoder B | D2 |
| Push button | D6 |
| Encoder and button commons | GND |

## Upload and test

1. Open `dual_rotary_encoder.ino` in the Arduino IDE.
2. Select **Arduino Uno** as the board. A classic ATmega328P Adafruit Metro
   can use the Uno board setting.
3. Select the board's serial port and upload the sketch.
4. Open Serial Monitor at **115200 baud**.
5. Turn each encoder and press/release the button. Expected lines are:

   ```text
   INNER,CW
   OUTER,CCW
   BUTTON,PRESSED
   BUTTON,RELEASED
   ```

If an encoder's clockwise direction appears reversed, swap that encoder's A
and B wires. If a detent produces no event or multiple events, change
`ENCODER_STEPS_PER_DETENT` in the sketch to `2` or `1` to match the encoder.

## Air Manager compatibility

This is a hardware test sketch, not Air Manager Knobster firmware. Air
Manager's documented DIY Knobster setup uses its own firmware flashing
workflow for a classic Arduino Nano. Uploading this sketch will not make the
Uno or Metro show up as an Air Manager Knobster.
