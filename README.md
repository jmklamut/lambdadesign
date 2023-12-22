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

The design of the electrical portion of the project after the board was done an Altium. A full schematic was created, tying all of the necessary components together. For feasibility of connecting I/O all across the enclosure, those I/O pins were made to be headers so that jumper cables could be used in the final design. This included the LCD display, the button, the programmer, slide pot, turn pot, power, speaker, LEDs, and the fan. Other components, such as the ATMega IC and oscillator were soldered directly on the board. 

In this design, while implementing the microSD reader to play WAV audio files on the speaker was not achieved in the verification stage, headers were placed to accommodate the microSD reader to allow the team to use it in a later configuration should we be able to implement it. (Further testing had the microSD reader to WAV audio playback working on an Arduino Uno, but implementation on the ATMega328P was never achieved.) Ultimately, these pins went unused in the final implementation of Bop It.  

![skecth](https://github.com/jmklamut/lambdadesign/assets/60929205/c97fe47e-05de-4a31-8857-3c985b5c04f1)

The next step taken in the design process was creating the PCB layout. The schematic in Altium was taken directly to a PCB layout. Components were placed as close to each other and oriented specifically to keep the board as small as possible. The final dimensions of the board were 3.25”x2.25”. The board was laid out using a two-sided design, with traces on both the top and bottom. The PCB layout is shown below. 

![pcb sponge](https://github.com/jmklamut/lambdadesign/assets/60929205/13248a22-f58e-4ff5-b946-6e85da320b2b)


## Software Implementation

The code for Arduino defines the game that combines physical input based on the lcd display and audio feedback. The code sets up the display, ports, LEDs, and inputs. Additionally, it uses the randomSeed() function to initialize the randomness of the game. 

Going through the void loop function, the first action is setting the LEDs LOW if a victory or loss was encountered prior in the program. After the initialization, the loop then hits a while loop that will continuously loop until the player hits the Stack It button. This condition is contained in the global variable playing_game. If the condition is met(playing_game == true), it will start the game. Once the stack it button is pressed, the code enters another while loop that checks for playing_game. Inside this loop is where we display and check for the correct user action. The code first stores the current position of the slider potentiometer and the spin potentiometer to be later used. The next step is to generate a random number for the random action the player will have to perform. I used the random() function to generate a number between 1-5, since there are four inputs. Once the number is generated, the lcd displays the action the user will perform. An audible cue is also executed.  

Since we are on the topic of sound, there are multiple sound functions that are implemented into this game. The first sound functions are stackTone, coolTone, flipTone, and sliceTone. These sound functions are essentially hardcoded beeps and bops of varying length that will play when the program displays an action for the user to perform. The second function is play_tone which uses predefined arrays of sounds along with the duration of each sound. The play_tone function will play the tone defined in the array for a duration of the value in the duration array. It will loop through that function until the array reaches the end. This function is used in the successful and incorrect functions that will later be described. 

Once the sound is played for each action, the code enters a loop based on two conditions: the first condition is if the user has not already performed an action, and the second condition is if the user completed an action in the threshold time. The threshold time starts at 4 seconds but decreases by 50 milliseconds after every input. We set a limit of 0.650 seconds making this the lowest possible threshold. Inside the while loop, the code checks for user input.  

The first input it checks is Flip-It. To check this, we created a function called flipped which takes a parameter of the current position of the potentiometer. If the potentiometer differs from the original position, the function will return true. The code takes the absolute value of this difference, so it doesn’t matter which way you flip it. The same logic is used for Slice-It because it is also a potentiometer. For Stack-It, the button is configured INPUT_PULLUP for debouncing. So, if the button is pressed, the function returns true by taking the negation of the button value (LOW == TRUE). Lastly for Cool-It, if the value of the voltage generated by the fan motor was above 60, the function would return true. 

If any of these conditions were meant, a global variable that corresponds with each input will be set to true.  Exiting the while loop, if else statements are used to determine a successful input, an incorrect input, or if time ran out for an input to be executed. The game indicates success if the action given by the random number generator is equal to the action performed by the user. If the user didn’t do anything, or if the user executed the wrong action, an incorrect input is indicated. After that, the global input variable is set back to false for the next user action. 

If a success is indicated, a success function is entered. This function will play a success tone and display to the lcd a successful attempt along with the score. To keep track of the score, we have a global variable that increases by 1 every time the success function is executed. In the success function, if the global score variable reaches 99, a victory tone will play and the lcd will display a winning message. Because winning the game also restarts it, the threshold is set back to 4000(4 seconds), score is set to zero, and playing game is set to false. This will make it, so the user has to Stack-It to start the game. 

If incorrect is detected, an incorrect function is entered. This function will play an incorrect tone and displays a you lost message along with the user score on the lcd. The game will then restart the same way the game is restarted if a victory is detected. 

Depending on a success, incorrect, or win the program will either continue inside the while playing loop or go to the very beginning of the void loop() function. If successful, the program will continue in the while playing loop. If incorrect, the program will go to the top of the void loop() function. Lastly, if the user wins, the program will also go to the top of the void loop() function. 

## Enclosure Design

Expanding on the Spongebob theme, it was decided that a stove-like enclosure would be created as the input components all implemented were an action that would be done in the context of making a burger, or in this context, a ‘krabby patty’. The overall stove was a laser cut box using the boxes.py program in SERC. The top of the box had holes to work as openings to connect the input components. Box cutout shown in Figure X. Then a smaller laser cut box was also created on the top of the stove to act as a stove display, cutout design shown in Figure Y. This stove display not only held the outputs of the project like the Liquid Crystal Display that indicated the actions and the LEDs that indicate the accuracy of the action, but it also acted as a support and enclosure to hide for the potentiometer for the spatula.  

![cutout sponge](https://github.com/jmklamut/lambdadesign/assets/60929205/b4473569-3964-40ce-9b94-39584f16be15)

The flip-it spatula input was 3-D printed and glued to a piece of plastic which fit in the indent of the metal part of the potentiometer. Two other inputs were also 3-D printed components glued to circuit components. The stack-it burger bun input which was glued to a standard push button, and the slice-it knife glued to the handle of a gliding potentiometer. Lastly, the cool-it fan was in the box to act like it was cooling the stove. The fan was on a raised surface to cover the wires but also bring the fan closer to the surface. The raised surface was extra acrylic sheets remaining from the laser cutter. The burger button was also attached to a raised surface that had a cutout exactly to the push button so it could support the button up. Any 3-D printed parts used designs from Thingiverse and were scaled to the desired size. The overall stove since it was like a box allowed for a lot of space to hold the printed circuit board and to contain the long wires that were needed to extend too all parts of the box. The box also contained the speaker that was an output to indicate which action is being called. The box was put together using the cut out holes from the design but some parts of the design needed to be superglued or hot-glued together. Some components were painted for visual appeal using acrylic paint such as the overall box, the burger bun and tomato slices.  

![buger](https://github.com/jmklamut/lambdadesign/assets/60929205/42c1f4f6-59fd-437d-9327-90e960aa2198)
![spat](https://github.com/jmklamut/lambdadesign/assets/60929205/c8ed104c-3090-43c8-81bb-7b8105908f6e)
![knife](https://github.com/jmklamut/lambdadesign/assets/60929205/52185608-2cb9-4e0b-af0f-3dfa6eb948db)
![cool](https://github.com/jmklamut/lambdadesign/assets/60929205/55c53f1a-8336-4406-891f-92c3a2a7485a)


## Assembly and System Integration

In assembling the final bop-it design, the first step was soldering onto the manufactured PCB. Components such as resistors, oscillator, caps were soldered directly on. The ATMega connection was made using a socket soldered directly on the board so that the chip could be replaced if need be. The voltage regulator was integrated using a three-pin female header directly on the board. Then, different numbered male headers were soldered on at the I/O component spaces. Next, each component was connected to a wire with a female jumper at the end. The wires were stripped and soldered to the pins of the I/O components. Then shrink wrap was shrunk around the junction using a heat gun. The figure below shoes where the slide potentiometer is placed on the back side of the lid with its pin soldered to wires and with shrink wrap. For the input voltage (>5V to Vreg), a 9V battery connector was cut and stripped. The positive end of the battery connector was connected to one terminal of a switch. The other terminal of that switch was tied to the voltage regulator.	The ground of the battery connector was tied to the ground on the PCB. After each of the external components had female jumpers on the end, all of those I/O components were connected to the headers on the PCB by jumper. From there, the circuit on the manufactured PCB was tested for the first time. One to two jumpers were used from each I/O (depending on where on the board that component would go and how far it’d have to reach), and so each component was able to be placed in the planned layout on the physical enclosure. With all of the circuit elements working correctly, the components were placed on the appropriate parts of the previously realized enclosure design. The motor/fan was glued to a platform off of the base of the inner enclosure, the button was fit into the sized square hole in the lid of the enclosure, the slide pot was taped on the underside to the backside of the lid, poking out through the appropriately-sized slit, and the potentiometer was placed in the upper enclosure platform, as well as the LCD display and LED’s. Finally, each component that had a connected prop (spatula, burger bun), those were glued on to the rotary pot and button respectively.  

![BopItSolderedPCB2](https://github.com/jmklamut/lambdadesign/assets/60929205/6157600c-f009-4513-8624-b8c57cf52960)
![BopItPCBwithComp](https://github.com/jmklamut/lambdadesign/assets/60929205/39882053-087f-40d2-a8c5-49799d5dc96f)

## Design Testing

After we assembled the PCB, we started our test to make sure the software and all the hardware components were correctly working. The general idea of testing on the PCB was the same as testing on the bread board, except this time it would be on a PCB. However, unlike the breadboard, we didn’t do any individual testing and went more the route of assembling the whole board and see what breaks. After assembling, our board wasn’t working.  We used a multimeter to make sure all of the components and pins were getting voltage. After this test, we quickly realized that the potentiometer and the speaker were our problem. All of the other components worked. When assembling our PCB, we soldered header pins on the board for practicality in testing. With that being said, we unplugged the speaker to focus on the first problem: the potentiometer. After going over the schematic, we realized that the potentiometer was plugged in wrong. Accordingly, we plugged the potentiometer correctly, and the PCB board worked perfectly with no sound. After testing different pins and voltages, we couldn’t figure out why the speaker wasn’t working. When testing the speaker originally, it worked connected to a computer through the programmer. This is when we realized that the battery might be the problem as the only difference was the power source. After an hour of confusion, we switched the battery connected to the PCB and the speaker started to work. The PCB was then transferred to the enclosure to begin the final assembly. 

![BopitProgrammingChip](https://github.com/jmklamut/lambdadesign/assets/60929205/0fbe4a5b-7ef3-4f6e-8e9c-e783b7259290)

Eventually, the bop-it was in full form with all I/O components connected and working properly, powered by a 9V battery. 

The following 3 videos show example gameplay with the SpongBop It! Toy. 

The first video is in youtube short form: 

https://www.youtube.com/shorts/wVkmvLuamyQ?feature=share 

The second video shows gameplay until a fail by not properly actuating the fan/cool it input 

https://www.youtube.com/watch?v=AP1-bo4IkPw 

The third gameplay shows gameplay until a fail by choosing the wrong input 

https://www.youtube.com/watch?v=56kfXUn5HIA 


## Summary

The SpongeBop-It proved to be successful and incorporated a proper implementation of the goal. We used different types of inputs and learned how to process all the different types of inputs and how to use it in the program. The game was successful and as a product worked well as it followed a popular theme that would be marketable and profitable. It was an experience to learn how to develop all the components of a product, from the hardware to the software to the enclosure design. Through troubleshooting and testing, we were able to debug some problems such as if we could not properly read in an input signal, and we also made some changes throughout the design. 

If we could make changes to improve out overall design, a change that could be made is to change the type of input that the cool-it function would use, because the fan used proved to be difficult to spin fast enough and the angle it is at in the enclosure makes it a little difficult to activate. It would also look more like a professional product as well as the stove could be closed and the inside and wires would not be exposed. Another change would be to use a microSD card component and output audio to indicate the actions for the game rather than the tones and written audio. This was our original plan but the audio did not properly play, so we decided to use a written display to indicate the actions. With or without these changes, the development of the SpongeBop-It was a successful project, showcasing effective implementation of a variety of inputs and comprehensive product design. 
