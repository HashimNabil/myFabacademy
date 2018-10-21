## ***Week 19: Project Development***

### ***What is the deadline? How much time do I have left?***

The deadline is at 28/6//2017. But I am writing this after I passed the deadline. As I spent more time in technical parts of the project, it was a very difficult situation

### ***What tasks have been completed, and what tasks remain?***

I finished desinging, fabricating and assembling the mechanical design which consists of the following:

- 6 3D printed wheels.
- laser cut frame.
- 3D printed differential

I also finished the electronic design and production of the electronic boards of the project which are 6 boards, one for each wheel and the main board which has bluetooth.

The interface program of the project is almost done with its beta stage. And I am also done with programing the DC motors.

What is remaining is linking the main board to one of the nodes to test the serial communication as I tried I2C and I could not implement it.

In addition, I need to debug the servo connections as the servo don't work well. I also need to replace the conical screws with flat ones to increase the stability of the frame and I need to replace two bearings with two holes of the rocker bogie linkage.

### ***What has worked? What hasn't?***

The blutooth to serial communication from the app to the main board worked but I need to make communication between the main board and the nodes. The DC motors are working just fine while I need to debug the servo connection of the boards. I am also missing voltage regulators and I need to buy as only one board has a working voltage regulator. Over all, I learned a lot from doing this project, and I will fix these issues later on to make the project work as I expected.

The differential system worked just fine and I am happy with that as I am electrical engineer and the aim of this project is to learn more about mechanical engineering so I focused more in these areas of the project.

### ***What questions need to be resolved?***

After implementing this project I realized that I should do it with iteration instead on focusing on the design, as I discovered a lot of things after assembling the project such as the need of using different type of screws, chaninge the maain bearing of the rocker and bogie joints to a hole with nut as well as strenghting the servo connection to the wheels. I also need to learn about I2C for future consideration as my boards are I2C ready but I can use them for serial communication which what I will do.

### ***What will happen when?***

I will fix the mechanical design and use serial communication instead of I2C for now but I will use I2C in the future.

### ***What have you learned?***

I learned many things and the most important thing is the significant importance of "iterative design" that I will try to do for the rest of the project that I will do in the future.
