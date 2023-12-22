# SpongeBop-It Final Report

**Team Lambda: Ben, John, and Angie**

## Design Overview

SpongeBop-It is a take on the traditional Bop-It game with a tasty twist. This bop-it game is based around making a krabby patty. Each input is based around an action that would be done while cooking a burger. The player will have to flip the burger, slice the tomatoes, cool the stove, and stack the burger. With the application of an ATMega328P microcontroller, a circuit was designed to incorporate all the inputs into a game, a random action is chosen and they must follow. The program coded and uploaded using and AVG Programmer and Arduino as the programming software, will carry out the game and allow interaction between the user and the device. The action chosen is displayed on a Liquid Crystal Display simultaneously with a tone sent out from a speaker to indicate an action has been called. Score is calculated each round as the time to perform each action is decreased slightly. The game will keep going until the user performs an incorrect action, misses the time frame, or successfully completes 99 actions. The inputs correspond with certain devices which include a push button, a sliding potentiometer, rotating potentiometer, and a fan.  

Originally, the game was inspired by the game Cooking Mama, because the many actions that go into one themed level of creating a certain meal. It was later decided to go with the Spongebob theme to make it more known. The original design sketch of the bop it is shown below. This design was carried out very similarly as shown in our final project.

![bopit skect](https://github.com/jmklamut/lambdadesign/assets/60929205/6d824607-afcb-42af-9a7d-44f1be08f978)
![final sponge](https://github.com/jmklamut/lambdadesign/assets/60929205/045813a2-f40f-416b-b0b4-9211ce14497e)

## Design Verification

To verify our design, we first tested each individual component. The first component we tested was the button or Stack-It! Testing the button was simple, we just had it print out on the LCD display we connected to the ATMega microcontroller. The second was testing the potentiometers. The first potentiometer was Flip-It. We verified this component by outputting the voltage on the LCD screen with a simple print statement in the loop function in Arduino. To verify the slide potentiometer, we did the same testing as the first potentiometer.  

![BopItBreadboardComp](https://github.com/jmklamut/lambdadesign/assets/60929205/57377243-d9b5-41da-927b-7688cf62cffe)

## Electronic Design Implementation

The electrical design was created in Altium, featuring a comprehensive schematic connecting components like LCD display, buttons, potentiometers, LEDs, and a fan. Headers were strategically placed for ease of I/O connections. The PCB layout was designed to minimize board size, utilizing a two-sided design. Although microSD audio playback wasn't implemented, provisions were made for future use.

## Software Implementation

The Arduino code defines the game's logic, combining physical input with LCD display and audio feedback. The game's loop manages user interactions, displaying actions, playing corresponding sounds, and evaluating user responses. Actions are based on randomized numbers, creating an engaging and dynamic gaming experience.

## Enclosure Design

The enclosure design, inspired by a stove, complements the culinary theme. Laser-cut acrylic components form the structure, and 3D-printed parts, such as the flip-it spatula, enhance the game's visual appeal. The overall design integrates all input components seamlessly.

## Assembly and System Integration

Assembly involved soldering components onto the PCB, connecting external components with wires, and integrating them into the enclosure. Rigorous testing ensured proper functionality before finalizing the assembly.

## Design Testing

Thorough testing, including multimeter checks and troubleshooting, identified and resolved issues related to the potentiometer and speaker. The final assembled *SpongeBop-It* demonstrated seamless operation and integration of hardware and software components.

## Budget and Cost Analysis

The estimated cost for manufacturing 10,000 units, including PCB manufacturing, hardware components, and enclosure materials, is approximately $793,140.

## Team

The team was divided into roles, with Angie focusing on enclosure and PCB, Ben on circuit design and hardware, and John on software. Collaborative efforts were emphasized throughout the project.

## Timeline

The project timeline included initiation, planning, execution, control, and project closure phases, detailing tasks performed, start and end dates, and team members involved.

## Summary

*SpongeBop-It* achieved success by effectively implementing a variety of inputs and comprehensive product design. The project provided valuable insights into hardware-software integration, troubleshooting, and iterative design processes. Future improvements could include refining the cool-it function and incorporating microSD audio for a more professional touch.
