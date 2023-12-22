# ShapeSpongeBop-It Final Report

**Team Lambda: Ben, John, and Angie**

## Design Overview

*SpongeBop-It* is a creative take on the classic Bop-It game, incorporating a culinary theme focused on making a Krabby Patty. Using an ATMega328P microcontroller, a circuit was designed to handle various inputs associated with cooking actions, such as flipping the burger, slicing tomatoes, cooling the stove, and stacking the burger. The game, implemented in Arduino, displays actions on an LCD and produces corresponding tones. Players must execute the action within a time frame, and the game continues until an incorrect action or a successful completion of 99 actions. Inputs include a push button, a sliding potentiometer, a rotating potentiometer, and a fan.

## Design Verification

Individual component testing was conducted to ensure proper functionality. Each input component was tested, including the button, potentiometers, and speaker. The design aimed for a cohesive integration of hardware and software elements.

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
