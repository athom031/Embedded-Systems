# Embedded Systems

This directory is a collection of projects completed in CS120B - Embedded Systems (UCR Spring 2020).

(Final Project => LCD Racer)

## Getting Started

### Prerequisites

Projects are built with:
* atmega1284p 8 bit microcontroller:
* AVR toolchain.
* ATATMEL-ICE-PCBA

### Compile

To run embedded system code change main.c file in source directory and to test project, change the test.gdb file in the test directory.

After doing so use the makefile to program atmega microcontroller or test your source file.

```
make program
```

```
make test
```

## Projects
<!--                    TABLE OF CONTENTS                                   -->
### Table of Contents
<div>    
    <html>
        <a href="#lcd">Final Project: LCD Racer</a><br/>
        <a href="#lab11">Lab 11: Task Scheduler</a><br/>
        <a href="#lab10">Lab 10: Concurrent synchSMs</a><br/>
        <a href="#lab9">Lab 9: PWM (Music Player)</a><br/>
        <a href="#lab8">Lab 8: ADC</a><br/>
        <a href="#lab7">Lab 7: LCD Screen</a><br/>
        <a href="#lab6">Lab 6: synchSMs</a><br/>
        <a href="#lab5">Lab 5: ATMega1284 Microcontroller Intro</a><br/>
        <a href="#lab4">Lab 4: State Machines</a><br/>
        <a href="#lab3">Lab 3: Bit Manipulation</a><br/>
        <a href="#lab2">Lab 2: AVR Toolchain Intro</a><br/>
    </html>
</div>
<br/>

<div id="lcd"></div>
<!--                           PROJECTS                                      -->

### Final Project: LCD Racer

#### LCD racing game. <br/>

Help player Smee (>) avoid the obstacles that ever increase in speed. <br/>
Try and beat your high score!

[Demo](https://youtu.be/kZFsC9rSBdo)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/LCDRacer)

<div id="lab11"></div>

### Lab 11: Task Scheduler

#### Part 1 
Code the keypad to be a SM task and implements a task scheduler to output the ASCII code for the character being pressed.
#### Part 2
Display the message "CS120 is Legend... wait for it DARY!". <br/>
The string does not fit on the display all at once, so the display scrolls through the text.
#### Part 3 
Implement a task scheduler to print the character last pressed.
#### Part 4
Have a string displayed that takes up the display and implement a task scheduler to iterate through the display index and output user characters over the string.

[Demo](https://youtu.be/onJCacxnShQ)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab11)

<div id="lab10"></div>

### Lab 10: Concurrent synchSMs

#### Part 1 
A concurrent SM that runs a SM for threeLDs to alternate each second and another SM blink a fourth light.
#### Part 2
An edited concurrent SM from the one above that "appears" to opperate on different periods.
#### Part 3 
An edited concurrent SM from the one above that now includes a speaker to be toggled every 2 ms.
#### Part 4
Includes user input to change what frequency the speaker outputs audio.

[Demo](https://youtu.be/swwiqgo0ODQ)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab10)

<div id="lab9"></div>

### Lab 9: PWM (Music Player)

#### Part 1 
With the PWM functionality, a designed system uses three buttons to play three different tones on a speaker.
#### Part 2
A SM that uses PWM functionality to scale through the C scale.
#### Part 3 
A SM that uses PWM functionality to play Kal Ho Na Ho theme.

[Demo](https://youtu.be/0He5l6V-2h0)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab9)

<div id="lab8"></div>

### Lab 8: ADC

#### Part 1 
A system that reads the 10-bit ADC result from a potentiometer and displays it on a LED array.
#### Part 2
A system that replaces the potentiometer with a photoresistor and displays it on a LED array.
#### Part 3 
A system that uses max and min results from previous lab to then only illuminate LED when enough light is detected on the photo resistor.
#### Part 4
A system, using a bank of eight LEDs, where the number of LEDs illuminated is a representation of how much light is detected. 

[Demo](https://youtu.be/WifXfBjOIZE)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab8)

<div id="lab7"></div>

### Lab 7: LCD Screen

#### Part 1 
Output a number that can be incremented or decremented with a button press.
#### Part 2
Cycling LED array cycle game, where score is incrememnted when the button is pressed and the middle light is illuminated.

[Demo](https://youtu.be/7MUxzIRRO7U)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab7)

<div id="lab6"></div>

### Lab 6: synchSMs

#### Part 1
A syncSM that blinks three LEDs in increasing and decreasing order, 1 second each.
#### Part 2
A simple light game that requires pressing a button when the middle light is illuminated. Pressing the light again restarts the game.
#### Part 3
LEDs represents bit # representation. Pressing one button increases the #, presssing another decreases the #.

[Demo](https://youtu.be/5JkeYeg2FGo)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab6)

<div id="lab5"></div>

### Lab 5: ATMega1284 Microcontroller Intro

#### Part 1
Based on the fuel tank given as input, have the lights warn what the fuel level is.
#### Part 2
Increment or decrement output with button presses.
#### Part 3
A festive light display.

[Demo](https://youtu.be/xjrFZ647MQU)
[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab5)

<div id="lab4"></div>

### Lab 4: State Machines

#### Part 1
Implemented on button and off button for an LED.
#### Part 2
Increment or decrement output based on button press.
#### Part 3
Digital combination deadbolt lock system for garage doorway.
#### Part 4
Extended dedadbolt where entering the lock key again will then lock the unlocked door.
#### Part 5
Further extended deadbolt that requires a 4-button sequence rather than 2-button sequence. This SM is instead represented with an array rather than a state for each button press.

[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab4)

<div id="lab3"></div>

### Lab 3: Bit Manipulation

#### Part 1
Output the number of the number of 1's on two input ports.
#### Part 2
Output fuel level based on fuel tank count.
#### Part 3
Extend fuel level output to flash light if seatbelt is not fastened and driver is seated.
#### Part 4
Take the upper nibble of PINA and map it to the lower nibble of PORTB and vice versa.
#### Part 5
Based on driver seat weight, siginfy whether or not the airbag is abled.

[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab3)

<div id="lab2"></div>

### Lab 2: AVR Toolchain Intro


#### Part 1
Illuminate an LED if the garage door is open at night.
#### Part 2
Output the number of available parking spaces in a parking garage.
#### Part 3
Extended available parking for a warning if parking lot is full.
#### Part 4
Weight sensor for amusement park ride with three seats that insures the weight is balanced.

[Source](https://github.com/athom031/EmbeddedSystems/tree/master/projects/source/Lab2)