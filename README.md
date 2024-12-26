# Moonlight
3D printed moon, turned into a light, controlled by neopixels and an AtTiny85

![Moonlight](./general/moon-light.gif)

## 3D Files
The STL of the moon is created by [moononournation](https://www.thingiverse.com/moononournation/designs).

Moon Lamp by moononournation on Thingiverse: (https://www.thingiverse.com/thing:2771919)

License: This thing was created by Thingiverse user moononournation, and is licensed under Creative Commons - Attribution - Non-Commercial

The stand is created by my, OBJ files in the [stl folder](./stl), [Fusion360 backup file](./general/moon%20statue.f3d) is available as well.

## Source code
The source code is written by myself and can be uploaded via the Arduino IDE to an ATtiny85.

License: Creative Commons - Attribution - Non-Commercial

## BOM
- ATtiny85
- 3 Neopixels, I used addressable LEDs from an LED strip
- USB cable
- perfboard
- hookup wire

## Construction of the circuit
1. Daisy-chain the Neopixels (5V, ground and data).
2. Connect the data wire to the 6th pin of the ATtiny85 (pin 2).
3. Cut off one of the USB cable connectors and find 5V and ground.
4. Connect the USB 5V lead to pin 8 on the ATtiny (VCC) and to the 5V lead on the Neopixels.
5. Connect the USB ground lead to pin 4 on the ATtiny (GND) and to the ground lead on the Neopixels.

That's all, folks.