# Space Invaders Bop-It

The Space Invaders Bop-It is an embedded interactive game that combines the reflex-based mechanics of Bop-It with the space-themed gameplay of Space Invaders. Built around the ATMega328P microcontroller, this project incorporates physical controls, audio/visual feedback, and a custom PCB to deliver an engaging and fast-paced user experience.

## Overview

Players are prompted with random commands such as:

- Turn Left
- Turn Right
- Throttle Up
- Shoot

Each command corresponds to one of the three physical inputs:
- Steering Wheel
- Throttle Lever
- Push Button

Correct responses increase the player’s score, flash a green LED, and play a "ding" sound. Incorrect or delayed responses trigger a red LED, a crash sound, and reset the game. The objective is to reach a score of 99 without failure.

## Features

- Three unique analog/digital inputs: steering, throttle, fire
- LCD screen to display real-time score
- DFPlayer Mini for audio feedback via speakers
- LED indicators for success and failure
- Finite State Machine logic with decreasing response time per successful input
- Enclosure design using Onshape CAD and laser-cut acrylic
- Custom PCB built in KiCad with support for power regulation, audio, and I/O

## Repository Structure

├── src/ # Arduino software
├── pcb/ # KiCad PCB design files
├── cad/ # CAD screenshots and Onshape link
├── docs/ # Final report and additional documentation
├── media/ # Photos and video demonstration
├── LICENSE
└── README.md


## How to Build

1. Clone this repository:
https://github.com/iamratedpg13/SpaceInvaders.git

2. Upload `src/main.ino` to an ATMega328P or Arduino Uno-compatible board.

3. Assemble the PCB using the files in the `pcb/` directory.

4. 3D print or laser cut enclosure parts using the files or images in `cad/`.

5. Copy required `.mp3` sound files to a FAT32-formatted microSD card and insert it into the DFPlayer Mini module.

6. Power the system using a regulated 5V supply (e.g., 9V battery with onboard regulator).

## Video Demo

Watch the game in action:  
https://www.youtube.com/watch?v=FF51uR-_Np4

## Key Implementation Notes

- The throttle and wheel are analog inputs (potentiometers); the button is digital.
- AVCC on the ATMega must be tied to 5V for proper ADC operation.
- Sound and display use UART and I2C, respectively; serial conflicts were resolved manually.
- Input drift was corrected in software by sampling baseline values at startup.

## Future Improvements

- Add OLED graphics for enhanced visuals
- Improve enclosure stability (consider wood or aluminum)
- Implement full Space Invaders game integration with inputs
- Modularize PCB for easier debugging and expansion

## Team Members

- PJ Granieri – Hardware and PCB Design
- Joshua Krymgold – Software Development
- Aragya Goyal – Enclosure Design and CAD

## License

This project is licensed under the MIT License. See the LICENSE file for details.

2. Upload `src/main.ino` to an ATMega328P or Arduino Uno-compatible board.

3. Assemble the PCB using the files in the `pcb/` directory.

4. 3D print or laser cut enclosure parts using the files or images in `cad/`.

5. Copy required `.mp3` sound files to a FAT32-formatted microSD card and insert it into the DFPlayer Mini module.

6. Power the system using a regulated 5V supply (e.g., 9V battery with onboard regulator).

## Video Demo

Watch the game in action:  
https://www.youtube.com/watch?v=FF51uR-_Np4

## Key Implementation Notes

- The throttle and wheel are analog inputs (potentiometers); the button is digital.
- AVCC on the ATMega must be tied to 5V for proper ADC operation.
- Sound and display use UART and I2C, respectively; serial conflicts were resolved manually.
- Input drift was corrected in software by sampling baseline values at startup.

## Future Improvements

- Add OLED graphics for enhanced visuals
- Improve enclosure stability (consider wood or aluminum)
- Implement full Space Invaders game integration with inputs
- Modularize PCB for easier debugging and expansion

## Team Members

- PJ Granieri – Hardware and PCB Design
- Joshua Krymgold – Software Development
- Aragya Goyal – Enclosure Design and CAD

## License

This project is licensed under the MIT License. See the LICENSE file for details.

