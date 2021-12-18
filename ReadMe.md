# Arduino-Macropad

A custom macropad built out of a Trellis Keypad, a display, rotary encoders and an Arduino


## Function

This macropad features 16 RGB-lit keys to program to your own pleasure! The display shows the name of each key, so you'll remember what each of these does. Also, thanks to the rotary encoders you are not limited to 16 keys, you can create aour own menu for every app you like. To switch between these menus, simply rotate the left encoder. The one on the right is used for media control, so you can adjust the volume and Play/Pause your music.

## Construction

### Materials and parts

| Part                                                     | Cost    | Links                                                        |
| -------------------------------------------------------- | ------- | ------------------------------------------------------------ |
| Raspberry Pi Pico                                        | 4.10 €  | [Berrybase](https://www.berrybase.de/neu/raspberry-pi-pico-rp2040-mikrocontroller-board?c=2461) |
| Sparkfun RGB Rotary Encoder (2x)                         | 9.30 €  | [Berrybase](https://www.berrybase.de/bauelemente/passive-bauelemente/potentiometer/drehimpulsgeber/rotary-encoder/inkrementalgeber-rgb-beleuchtet) |
| Rotary knob, transparent (2x)                            | 1.80 €  | [Berrybase](https://www.berrybase.de/bauelemente/passive-bauelemente/potentiometer/drehpotis/drehknopf-f-252-r-ger-228-ndelte-6-0mm-achse-transparent) |
| Adafruit NeoTrellis Driver PCB                           | 12.90 € | [Berrybase](https://www.berrybase.de/neu/adafruit-neotrellis-rgb-treiber-pcb-f-252-r-4x4-keypad?c=2434) |
| Adafruit Silikon Elastomer 4x4 Button Keypad             | 5.10 €  | [Berrybase](https://www.berrybase.de/sensoren-module/eingabe/adafruit-silikon-elastomer-4x4-button-keypad-f-252-r-3mm-leds) |
| Monochromes 1.3" 128x64 OLED Display - STEMMA QT / Qwiic | 20.55 € | [Berrybase](https://www.berrybase.de/sensoren-module/displays/oled-displays/monochromes-1.3-128x64-oled-display-stemma-qt/qwiic) |
| Screws, 3mm in diameter, 16mm in length (4x)             | ?       | had them laying around                                       |

### 3D-prints

I designed my own case and printed it with PLA ([Blue Pearl](https://www.dasfilament.de/filament-spulen/pla-1-75-mm/405/pla-filament-1-75-mm-blue-pearl?c=11)). I've put the Skynet logo on the front, because I felt the need to put something there and I have just watched Terminator 2. You can find the CAD and STL files in `doc/cad-files/`.

### Assembly

1. Wiring:
	There are some images of the wiring in the `doc` folder. However, there are some errors in the schematics that I haven't fixed yet.
2. Putting the parts together:
	I used four screws with a diameter of 3mm and a length of 16mm
	I taped some foam on top of the legs for the trellis board, so it can't wiggle too much



## Programming

### Platform
I chose the Raspberry Pi Pico because of its speed and ability to emulate a keyboard. But for the programming part I sticked with the Arduino platform, because I already know how it works and is compatible with all devices. This was a problem with micropython, as it doesn't have widespread support for every module imaginable. I also decided myself against Cuircuit-Python, once because using a display with it is kinda a struggle, second because I programmed enough Python in the past, and I wanted to practice a little bit of C++.

Secondly, as I had some trouble sending special keycodes (Volume UP and DOWN, Play/Pause, etc) with the Keyboard-library, I decided to send a special shortcut instead, wich would be caught by an AutoHotKey script (It's Windows only, sadly, other platforms would need to search for an alternative).

### Source-Code for RPi Pico

The source-code is divided into different files, here is a short summary of them:

| file                  | description                                                  |
| --------------------- | ------------------------------------------------------------ |
| **Pico-Macropad.ino** | main file, brings everything together by telling the other modules what to do |
| config.h              | saves the configuration of shrotcuts                         |
| display.h             | controls the OLED-display                                    |
| display_animation.h   | saves data for the startup-animation on the display          |
| led_controller.h      | responsible for setting the brightness of all the leds       |
| neotrellis.h          | controls and reads the Adafruit Neotrellis board             |
| rotary_encoder.h      | controls and reads the two rotary encoders                   |
| shortcut.h            | uses the the `Keyboard.h`-library to send the sortcuts to your PC |
| *macropad.ahk*        | the AHK-script. Its at least responsible for the Volume and Play/Pause |



### AutoHotKey-Script

At first I wanted to create every shortcut inside the C++-program. However, I wanted to build a [config-creator](https://github.com/zauberwild/Pico-Macropad-Config-Creator) to create the shortcuts with a GUI. This means, that the Pico will send a generic shortcut (`F24` + something), which will be ctched by an AHK-script. Finally, the script will perform all the tasks.




## Credits and License

This project is under the MIT license. If you reuse any parts of this and publish it, please be so kind to mention me / this repo.
