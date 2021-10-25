# Introduction To Robotics

Repository dedicated to the assignments from the course "Introduction To Robotics", taken as a 3rd year Computer Science student at the University of Bucharest. The repository contains Arduino Code in the purpose of proper functioning of the circuits or devices build during classes.
 
 
## Homework 1 - Manipulation of a RGB LED

### Requirements

-Components:RBG led (1 minimum), potentiometers (3 minimum), re-sistors and wires (per logic)
-Technical Task:Use a separat potentiometer in controlling each of thecolor of the RGB led (Red,Green andBlue).  The control must be donewithdigital electronics(aka you must read the value of the potentiome-ter with Arduino, and write a mapped value to each of the pins connectedto the led.!

### Picture of the setup
[WhatsApp Image 2021-10-25 at 16 29 58](https://user-images.githubusercontent.com/41392462/138708154-b5453248-f288-45c7-8663-9ead6e018ecb.jpeg)

### Code source details
In the first place were set all the constant values and global variables needed, such :
- potentiometers initial read values (all set to 0)
- led pin values (11, 10, 9)
- potentiometers pins values (A0, A1, A2)
- initial intensity for each color (all set to 0)
- maximum value of a potentiometer (1023)
- maximum value of a led color (255)
In the setup function, the led pins are set as the output and the potentiometers pins as the input. 
In the loop function, the code is constantly reading the potentiometers values which are mapped and saved in the intensityBlue, intensityRed, intensityGreen variables in order 
to set each color of the led. 
Function 'setColor' receives as parameters the converted values from potentiometers values(values in the range [0, 1023]) into suitable led values (values in the range [0,255])
and shows on the led the proper color with its chosen intensity.
### Link to video showcasing functionality
https://www.youtube.com/watch?v=ZxrsoGaaSPU&ab_channel=BiancaLarisa
