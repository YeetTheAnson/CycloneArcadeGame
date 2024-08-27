# CycloneArcadeGame
A replica of the cyclone (rigged game) in arcades.

![CycloneArcadeGame](https://github.com/YeetTheAnson/CycloneArcadeGame/raw/main/1.png)

Watch the demo video below

[![CycloneArcadeGame](https://img.youtube.com/vi/xrOE913GWf0/0.jpg)](https://www.youtube.com/watch?v=xrOE913GWf0)


# Getting started

1. Flash the ESP32 by compiling the code yourself or flashing the binary or running it in a simulation
    - [Compile and flash](#how-to-compile-ino-file-and-flash)
    - [Flash binary](#how-to-flash-binary)
    - [Simulation](#how-to-run-in-simulator)
2. Learn how to play the game [here](#usage)
4. Learn about the features [here](#features)


## How to compile ino file and flash

1. Navigate to `WokwiFiles` and open the `CycloneArcadeGame.ino` file in Arduino IDE.
2. Open library manager and install `Adafruit_NeoPixel` and `Adafruit_SSD1306 `
3. Add ESP32 to the board manager:
    - Go to `File` >> `Preferences` >> `Additional Boards Manager URLs`
    - Paste the following URL: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
4. Select the board `ESP32S2 DEV MODULE`.
5. Press compile and flash the code to the ESP32S2.


## How to flash binary

1. Type ```https://github.com/espressif/esptool``` into CMD
2. Navigate to the correct folder with ```cd esptool```
3. Type ```git clone https://github.com/YeetTheAnson/CycloneArcadeGame```  into CMD
4. Type ```esptool.py --chip esp32 erase_flash``` to erase flash
5. Type ```esptool.py --chip esp32 --port COMX --baud 115200 write_flash -z 0x1000 CycloneArcadeGame/CompiledBinaries/CycloneArcadeGameMerged.bin``` and replace COMX with your COM number


## How to run in simulator

1. Open VSCode and install Wokwi plugin
2. Open the `WokwiFiles` folder in VSCode
3. Open `diagram.json` and press the run button


# Usage

1. Press the button at the point where the led is (Shown in video)
2. LED will flash green, and OLED will display 'You Win' of you win
3. Type in `mastermode` to enter the master menu. The password is `HackClubArcade`
4. Press the button to switch between game speed and rigged percentage in master menu
5. Type in `exitmastermode` to return to normal game

## Features
- Game master can set rigged percentage and speed