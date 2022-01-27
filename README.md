# Remotely-Monitor-The-Automatic-Debugging-Robotic-Arm

When the Pixetto lens determines that the object is the color of the defect, the conveyor belt stops running and the robotic arm clamps the place where the article is placed, and conversely, the conveyor belt runs, and the robotic arm presents its initial state

# Install

After following the first three steps below, please note that the image from step 4 must come out, otherwise you cannot enter the Pixetto and Adafruit PWM Servo Driver Library

![jpg](sample_1.jpg)
![png](sample_2.png)

# Usage
#### Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver()

Variable pwm controls the six-axis robotic arm motor

#### Pixetto ss(A0,A1)

Variable ss control the Pixelto lens, where A0 and A1 are RX and TX angles, respectively

# Methods

# License
(c) 2022 Qing Wei Lin. MIT License
