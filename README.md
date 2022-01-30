# Remotely-Monitor-The-Automatic-Debugging-Robotic-Arm

When the Pixetto lens determines that the object is the color of the defect, the conveyor belt stops running and the robotic arm clamps the place where the article is placed, and conversely, the conveyor belt runs, and the robotic arm presents its initial state

# Install

After following the first three steps below, please note that the image from step 4 must come out, otherwise you cannot enter the Pixetto and Adafruit PWM Servo Driver Library

![jpg](sample_1.jpg)
![png](sample_2.png)

# Usage

### Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver()
called this way, it uses the default address 0x40

### Pixetto ss(A5,A4)
Pixetto ss (A5, A4) is a program generated by the VIA Pixetto software block, the following are the programs and tiles generated by VIA Pixetto and the Arduino IDE
<br>VIA Pixetto tile：<br>
![png](sample_3.png)
<br>Arduino IDE Code：
```C++
#include<Pixetto.h> 
Pixetto ss(A5,A4);  //define RX、TX pin
void setup()
{
  ss.begin(); 
}
```

# Method

### pwm.setPWMFreq(freq)
#### Description
This function can be used to adjust the PWM frequency, which determines how many full 'pulses' per second are generated by the IC. Stated differently, the frequency determines how 'long' each pulse is in duration from start to finish, taking into account both the high and low segments of the pulse.

Frequency is important in PWM, since setting the frequency too high with a very small duty cycle can cause problems, since the 'rise time' of the signal (the time it takes to go from 0V to VCC) may be longer than the time the signal is active, and the PWM output will appear smoothed out and may not even reach VCC, potentially causing a number of problems.

#### Arguments
  * freq: A number representing the frequency in Hz, between 40 and 1600
#### Example
The following code will set the PWM frequency to 1000Hz:
```C++
pwm.setPWMFreq(1000)
```
### pwm.setPWM(channel, on, off)
#### Description
This function sets the start (on) and end (off) of the high segment of the PWM pulse on a specific channel.  You specify the 'tick' value between 0..4095 when the signal will turn on, and when it will turn off.  Channel indicates which of the 16 PWM outputs should be updated with the new values.

#### Arguments
  * channel: The channel that should be updated with the new values (0..15)
  * on: The tick (between 0..4095) when the signal should transition from low to high
  * off:the tick (between 0..4095) when the signal should transition from high to low
#### Example
The following example will cause channel 15 to start low, go high around 25% into the pulse (tick 1024 out of 4096), transition back to low 75% into the pulse (tick 3072), and remain low for the last 25% of the pulse:
```C++
pwm.setPWM(15, 1024, 3072)
```
# Further reading
 * [Adafruit PCA9685 16-Channel Servo Driver](https://learn.adafruit.com/16-channel-pwm-servo-driver/library-reference?view=all)
 * [Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
 * [VIA_Pixetto](https://pixetto.ai/tutorials/)

# License
(c) 2022 Qing Wei Lin. MIT License
