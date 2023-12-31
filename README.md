# AgCabLab Joystick
> Arduino code to interface the AgCabLab software with tractor cab steering wheel and console buttons.

The AgCabLab was an interactive exhibit that engaged the public in better understanding where their food comes from. The AgCabLab was showcased at county and state fairs across North Dakota, Minnesota, and Wisconsin. There was also one installed at the North Dakota Heritage Center & Museum in Bismarck, ND.

The AgCab itself was an actual tractor cab donated by Case IH. The steering wheel and console buttons were wired up to an Arduino microcontroller and computer. The computer ran custom made software that allowed kids and adults to drive a tractor around a field and harvest crops.

![AgCabLab](/photos/agcablab.jpg)

## Configurations

There were different generations of tractor and combine cabs donated by Case IH. A different code base was developed for each instance.

```
/agcablab-joystick
+—/combine_controller
+—/ethanol_controller
+—/heritage_tractor
+—/rochester_controller
+—/vcsu_barnes_controller
```

### Optical Encoder

A rotary optical encoder by Honeywell (600128CBL) was mounted to the tractor cab’s steering column and would rotate with the steering wheel.

The sensor data would be captured by the Arduino and passed to the computer as the controller’s horizontal axis.

### Console Input

Buttons and levers on the tractor cab’s console were also employed to send data to the computer.

Buttons would raise or lower the agricultural machinery, like plows and planters. The throttle was usually a potentiometer that would be configured as the controller’s vertical axis.

## Arduino Model

The [Arduino Leonardo](https://docs.arduino.cc/hardware/leonardo) model was used for the project.

The Leonardo has built-in USB communication that allows the Micro to appear as a mouse and keyboard when plugged into the computer. And more importantly, it could be configured to act as a video game controller (not all boards have this ability).

## Assembly

The Adafruit [Proto-Screwshield (Wingshield) R3 kit](https://www.adafruit.com/product/196) was used for making wire connections to the Arduino’s analog and digital inputs without having to solder each wire to the board. It’s highly recommended.

![Adafruit Proto-Screwshild](/photos/wing-shield.jpg)

## Testing

Testing the Arduino input was possible with the [Joystick Show](https://apps.apple.com/ca/app/joystick-show/id515886877?mt=12) app available for macOS. Though, any app capable of reading game controller input would work just as well.

## Links

- AgCabLab homepage: https://www.aginspire.org/
- Repository: https://github.com/johnaboucha/agcablab-joystick

## Licensing

The code in this project is licensed under MIT license.