# Introduction To Robotics

Repository dedicated to the assignments from the course "Introduction To Robotics", taken as a 3rd year Computer Science student at the University of Bucharest. The repository contains Arduino Code in the purpose of proper functioning of the circuits or devices build during classes.
 
 
## Homework 1 - Manipulation of a RGB LED

### Requirements

-Components:RBG led (1 minimum), potentiometers (3 minimum), re-sistors and wires (per logic)
-Technical Task:Use a separat potentiometer in controlling each of thecolor of the RGB led (Red,Green andBlue).  The control must be donewithdigital electronics(aka you must read the value of the potentiome-ter with Arduino, and write a mapped value to each of the pins connectedto the led.!

### Picture of the setup
![alt text](https://user-images.githubusercontent.com/41392462/138708154-b5453248-f288-45c7-8663-9ead6e018ecb.jpeg)

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

## Homework 2 - Traffic lights for crosswalk
### Requirements
The homework consists of the following:
- Components:  5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)
- General  description:Building  the  traffic  lights  for  a  crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green)and 3 LEDs to represent the traffic lights for cars (red, yellow and green).See the states it needs to go through.  If anything is not clear, ask.  Also,see the uploaded video (the intervals are different, but the states flow isthe same).  It’s a traffic lights system for people and cars - don’t overthinkit.
#### The system has the following states:
1. State 1(default, reinstated after state 4 ends):  green light for cars,red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  bypressing the button.
2. State 2(initiated by counting down 10 seconds after a button press):the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds.Duration:  3 seconds.
3. State 3(iniated after state 2 ends): red for cars, green for people anda beeping sound from the buzzer at a constant interval. Duration:10 seconds.
4. State 4(initiated after state 3 ends):  red for cars,blinking greenfor people and a beeping sound from the buzzer,  at a constant in-terval, faster than the beeping in state 3.This state should last 5seconds.
Be careful:  pressing  the  button  in  any  state  other  than  state  1  should NOT yield any actions.

### Picture of the setup
![alt text](https://user-images.githubusercontent.com/41392462/140074018-69bcb168-592a-4658-9b8f-74dee839a33a.jpg)

### Link to video showcasing functionality
https://www.youtube.com/watch?v=XopwuBzEMZA&ab_channel=BiancaLarisa

## Homework 3 - EMF Detector(Ghost Detector)
### Requirements
The homework consists of the following components:
- a buzzer and a 7-segment display (or a led bar / or 8 ledsin a row that simulate a led bar)
- Task:should detect EMF (check body and near outlets.DO NOT IN-SERT INTO OUTLET). It should printthe value on the 7-segment display (or light the led bar)andshould makea sound based on the intensity.
- The catch:it’s really easy,  but one of  the mistakes you can do is notcalibrate for the interval on the values you are going to get. 
### Picture of the setup
![alt text]!(https://user-images.githubusercontent.com/41392462/140768503-a37edcea-ff1d-4305-a163-4cc5f80fa05a.jpg)

### Link to video showcasing functionality
https://www.youtube.com/watch?v=OcYLy97b0Es&feature=youtu.be&ab_channel=BiancaLarisa
