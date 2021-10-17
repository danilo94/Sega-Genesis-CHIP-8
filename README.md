# Sega Genesis CHIP-8 Interpreter

## Another CHIP-8 interpreter, but for Sega Genesis
This project is a very simple CHIP-8 interpreter based on [multigesture.net](https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/) implementation ported to Sega Genesis systems.


![CHIP-8 SGDK](https://github.com/danilo94/Sega-Genesis-CHIP-8/blob/main/imgs/image.png)


## Features

- Menu with 3 Game Options:
	- Invaders (Space Invaders Clone)
	- Tank
	- Boat
- A Python script to load .ch8 files and convert to **u8 \*data**;

## HOW TO RUN
- Compile this code, or download the .bin file.
- Load  normally, using your preffered Sega Genesis Emulator.
- Load to your SD card, and run the interpreter using a Flash Card.
- To Select a game, just use the menu (**UP** and **DOWN** buttons) and press the **Start** button.
- To exit a game and goes to the menu just press **Start**.


## Limitations
- Recurrent application Slowdowns, due the current tile drawing logic used.
- Only 7 buttons of sega genesis  joystick mapped to CHIP-8  core.

## Requirements to compile

- [SGDK](https://github.com/Stephane-D/SGDK)
- An IDE of your preference ( to write this project I using VSCode with [Genesis Code](https://github.com/zerasul/genesis-code) extension).


## Acknowledges
- Thanks to [multigesture.net](https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/), to provide a very well documented code, and explanation about how the CHIP-8 works.
- Thanks to [SGDK](https://github.com/Stephane-D/SGDK) team.
- Thanks to [Zerasul](https://github.com/zerasul/genesis-code), to provide a vscode extension to manage, compile and create projects directly on VSCode.
