#include<Pixetto.h>                                        // Import the Pixelto library                                
#include <Adafruit_PWMServoDriver.h>                       // Import the PCA9685 driver library
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();   // Call the servo driver function, the default I2C address is 0x40

#define SERVOMIN  125                                      // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575                                      // this is the 'maximum' pulse length count (out of 4096)

Pixetto ss(A0,A1);                                         // define Pixetto RX pin、TX pin

void setup()
{
  ss.begin();                                     
  pwm.begin();
  
  pwm.setPWMFreq(60);                                      // Analog servos run at ~60 Hz updates
  
  Serial.begin(9600);
  pinMode(4, OUTPUT);                                      // Conveyor belt motor output
}


void loop()
{
  if (ss.isDetected()) {
    digitalWrite(4, HIGH);
    Initialize();
    //28 ~ 32code The lens recognizes black, and the conveyor belt continues to execute, otherwise it stops
    if (ss.isDetected() == ss.getFuncID() == Pixetto::FUNC_COLOR_DETECTION && ss.getTypeID() == Pixetto::COLOR_BLACK) {
      Serial.println("BLACK");
      digitalWrite(4, HIGH);
      Initialize();
    }
    //34 ~ 50code The lens recognizes red, and the conveyor belt stops
    if (ss.isDetected() == ss.getFuncID() == Pixetto::FUNC_COLOR_DETECTION && ss.getTypeID() == Pixetto::COLOR_RED) {
      //delay(1 * 1000);
      Serial.println("RED");
      digitalWrite(4, LOW);
      Initialize();
      delay(500);
      down();
      delay(500);
      grap();
      delay(500);
      up();
      delay(500);
      putup();
      delay(500);
      Initialize();
      delay(500);
    }
  }
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);         // map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

// Robotic arm initialization action
void Initialize() {
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(50) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(65) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(30) );
  //pwm.setPWM(servo6, 0, angleToPulse(30) );
}


// Go down and prepare the clip
void down(){
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(60) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(65) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(30) );
}

void grap(){
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(60) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(65) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(180) );
}

// Lift up after clamping
void up(){
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(55) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(65) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(180) );
  delay(500);
}

// Place it forward after clamping
void putup(){
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(55) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(90) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(30) );
  delay(500);
}
