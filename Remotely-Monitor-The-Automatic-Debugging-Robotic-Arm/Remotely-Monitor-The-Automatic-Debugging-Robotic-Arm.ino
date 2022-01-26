#include<Pixetto.h>                                        //匯入鏡頭Pixetto函式庫                                
#include <Adafruit_PWMServoDriver.h>                       //匯入PCA9685驅動程式函式庫
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();   // 呼叫伺服驅動程式函數，預設I2C位址為 0x40

#define SERVOMIN  125 // 這是“最小”脈衝長度計數（在4096)
#define SERVOMAX  575 // 這是“最大”脈衝長度計數（在4096)

Pixetto ss(A0,A1);                                //定義Pixetto RX、TX腳位

void setup()
{
  ss.begin();                                     //Pixetto開始辨識
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  Serial.begin(9600);
  pinMode(4, OUTPUT);                             //運輸帶馬達輸出
}


void loop()
{
  if (ss.isDetected()) {
    digitalWrite(4, HIGH);
    Initialize();
    //28 ~ 32 鏡頭辨識到黑色，運輸帶繼續執行，否則停下
    if (ss.isDetected() == ss.getFuncID() == Pixetto::FUNC_COLOR_DETECTION && ss.getTypeID() == Pixetto::COLOR_BLACK) {
      Serial.println("BLACK");
      digitalWrite(4, HIGH);
      Initialize();
    }
    //34 ~ 50 鏡頭辨識到紅色，則運輸帶停下
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
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

//pwm.setPWM(PCA9685腳位, 角度1, 角度2)，角度1會轉到角度2
//Ex:pwm.setPWM(0, 0, angleToPulse(5))，腳位0，馬達從0轉到5度

void Initialize() {     //機械手臂初始化動作
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(50) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(65) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(30) );
  //pwm.setPWM(servo6, 0, angleToPulse(30) );
}


//往下準備夾
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

//夾完之後往上抬
void up(){
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(55) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(65) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(180) );
  delay(500);
}

//夾完後向前放
void putup(){
  pwm.setPWM(0, 0, angleToPulse(5) );
  pwm.setPWM(1, 0, angleToPulse(55) );
  pwm.setPWM(2, 0, angleToPulse(120) );
  pwm.setPWM(3, 0, angleToPulse(90) );
  pwm.setPWM(4, 0, angleToPulse(0) );
  pwm.setPWM(5, 0, angleToPulse(30) );
  delay(500);
}
