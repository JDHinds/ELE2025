# ELE2025 - Autonumous Line-Following Machine Project

## Weekly Design Report

### [David Gardiner](mailto:dgardiner04@qub.ac.uk)

| Image | Week | Progress |
|-------|------|----------|
| ![](img/david.jpg) | 16/01/24 | Met with team; |
| | 23/01/24 | Identification of errors from previous lab’s code and correction of wire placement from Arduino to Motor Driver Board to get motors operating correctly with PWM signals and button input.  Wiring of Encoder to Arduino and testing of code to check the serial monitor values increment with motor rotations. Carried out the Risk Assesment.|
| | 30/01/24 | Wiring of Encoder on second motor to Arduino and testing of code to check the serial monitor values increment with motor rotations for both motors.  Connection of battery instead of power supply to allow for wireless movement.  Research of Infrared Line Tracking Sensor to determine the wiring and potential code to be used.|
| | 06/02/24 | Wiring and coding of Infrared Line Tracking Sensor to detect a difference between white and black on a page.  Glued wheels and fitted stabilising wheel from old chassis onto new chassis.|
| | 13/02/24 | Reading Week.|
| | 20/02/24 | Building of new chassis and fitting of components.  IR Sensors working, and trial code uploaded to test on track.  Changed sensors to back and reversed motor direction in code to allow for more sharp cornering.|
| | 22/02/24 | Robot now completes the cornering section of the course.|
| | 27/02/24 | Adjustment of motor speeds to complete course faster.  Wiring and coding of encoder to allow motor speed to be monitored.|
| | 29/02/24 | IR Sensors fitted with screws and 2 additional sensors added.  Interrupt code added to enable outside sensors to enable the last used code to run when the line is overshot, allowing faster speeds to be achieved within course.|
| | 05/03/24 | Fixing of motors and wires after damage caused when stored, causing setbacks to progress.  Added 2 rail breadboard to provide additional 5V and Ground pins which can be accessed easily.  Code fixed and ball pushing code implemented with original line following code to enable the complete course to be completed in 18 seconds.  Soldering of wires to bluetooth module and wiring completed. |
| | 07/03/24 | Adjustment of motor speeds and adding speed restriction at end of course to allow more control for ball pushing section of course.  Autonomous mode is now complete. |
| | 08/03/24 | Wiring of Robot was tampered with and motors were removed and driving shafts broken.  Spent time identifing wiring issues. |
| | 11/03/24 | New motors fitted and testing of code implementation with Jude. |

### [Jude Hinds](mailto:jhinds04@qub.ac.uk)

| Image | Week | Progress |
|-------|------|----------|
| ![](img/jude.jpg) | 16/01/24 | Met with team; chosen as team leader; appointed as Programming Lead, and wrote the code for the tasks in the first lab. Was unable to verify code due to technical issues. |
| | 23/01/24 | Fixed code from last week's lab; wrote RotationUsingEncoder code. Carried out the Risk Assesment. |
| | 30/01/24 | Worked on Sensors Lab |
| | 06/02/24 | Reserched and Assembeled HC-05 Module. Discovered Flutter SerialPort library. |
| | 13/02/24 | Reading Week - was occupied with other assignments |
| | 20/02/24 | Made JSON Serialisable class for reading data in and out of the serial monitor. Serial monitor cannot yet be read accurately. |
| | 27/02/24 | Flutter program now accurately read serial monitor. |
| | 05/03/24 | Program can now read and write states to the board. Now working on finalising line following algorithm w/ David. |

### [Oran Farrell](mailto:ofarrell03@qub.ac.uk)

| Image | Week | Progress |
|-------|------|----------|
| ![](img/oran.jpg) | 16/01/24 | Met with team; |
| | 30/01/24 | Began the design of the robot. Decided on a two tier, two wheel system with a stabliser wheel at the back. Have a basic schematic drawn out on paper, need to move this onto Fusion 360. | 
| | 05/02/24  | Completed a basic design mock-up on fusion 360. 2 basic panels, 150mm, 100mm, 5mm. Each panel has 4 holes located in corners 10mm in diameter. the bottom panel additional has a hole at the back, (30mm in diameter) which is for the stablising wheel. the pilers are 60mm tall and 10mm in diameter. |
| | 13/02/24 | Reading Week.|
| | 20/02/24 | Designed a wedge on CAD to attached to front two bars to help maneuver the ball into the set position at the end. |
| | 27/02/24 | Had to redesign the wedge as the sensors were hitting the ball. Left a larger gap to stop this problem. Started working towards the presentation.|
| | 05/03/24 | Continued working on the presentation. |


### [Conrad Quinn](mailto:cquinn167@qub.ac.uk)

| Image | Week | Progress |
|-------|------|----------|
| ![](img/conrad.jpg) | 16/01/24 | Met with team; |
| | 23/01/24 | Worked on the proportional control algorithm code using Arduino. |
| | 30/01/24 | Made a start on the code that will be used to implement the Infrared Sensors to help with the line tracking. |

# To-Do

- [ ] Make shell for board
- [ ] Get and integrate sensors

- [ ] Write Arduino code for Line-Following
- [ ] Write Arduino code for ball pushing
- [ ] Write Ardiuno Code for HC-05 module
- [ ] Write application to interface with HC-05
  - [ ] Getting and displaying telemetrics
