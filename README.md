# UFO PCB Lamp

## Overview:
This is a PCB lamp that I started in a workshop. The PCB light ring and [Arduino Nano 33 BLE Sense Rev2](https://docs.arduino.cc/hardware/nano-33-ble-sense-rev2/) board were provided. Instructions from the workshop are [here](https://hackaday.io/project/192881/instructions).

I later expanded upon the provided arduino code and created the 3d models using Onshape so that it looks like a UFO. The lamp operates using the Rev2 board's proximity and gesture sensors.

## Project Aspects

### 3D Model 
Using onshape, I improved the 3d model design by having the UFO connect to the lamp neck. Now I don't have to use hot glue to precariously attach them together. 
<br/>
Future improvements aim to add screwholes so I can screw the PCB light ring to the UFO and to add a lid to the electronics (with a switch to turn it on and off)

### PCB Light ring
Currently, the light ring is able to cycle through preset colors whenever a gesture is detected. 

### PCB Board
The PCB board has the arduino, ribbon cable plug and battery pack soldered onto it. I don't know what the button on the PCB board does or what pin it is connected to. I should probably use a multimeter to see which pin on the arudino board it's connected to. I hope to add functionality to the button maybe to switch between different arrays holding different colors.
<br/>
Future goals is to determine what pin the button is connected to and to insert an on-off switch between the battery pack and the arduino. This probably involves desoldering the battery pack and then raising it somehow in order to connect a switch.

### Bluetooth
I am still learning how to use the Arduino BLE stuff. I think I will first try following [this tutorial](https://docs.arduino.cc/tutorials/nano-33-ble/bluetooth/) before trying to implement it into this project.
<br/>
The idea is to be able to turn off the gesture detector and be able to control what color the light is via the magic of bluetooth. 