#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

char input='i'; 

// our servo # counter
uint8_t servonum = 0;

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
int in1 = 7;
int in2 = 2;
int ena = 3;

//Right motor
int in3 = 12;
int in4 = 13;
int enb = 5;

int IN1 = in1;
int IN2 = in2;
int ENA = ena;

//Right motor
int IN3 = in3;
int IN4 = in4;
int ENB = enb;

void setup() {
  Serial.begin(9600);
  //pinMode(13,OUTPUT);
  Serial.println("8 channel Servo test!");

  pwm.begin(); 
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  pinMode(8,OUTPUT);//8=dir, 9=brk;6=pwm
  pinMode(9,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);



  
  //yield();
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 340;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
    
      if(Serial.available()>0){
      input = Serial.read();
      Serial.println(input);
    }

  //upper motion of the wheels code starts
    
    if(input == 'V'){
    
      //move forward(all motors rotate in forward direction)
      Serial.println("Forward");
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
    }
    
    else if(input == 'v'){      //move reverse (all motors rotate in reverse direction)
      Serial.println("Backward");
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
    
    }
    
    else if(input == 'S'){      //stop
      Serial.println("STOP");
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
    }
  
// racks motion code starts
  if(input=='F')//for vertical compression motion of 
  {
    for( int angle =0; angle<100; angle +=20){
      Serial.println(angle);
      pwm.setPWM(0, 0, angleToPulse(angle) );
      pwm.setPWM(2, 0, angleToPulse(angle) );
      break;
    }

    for( int angle =100; angle>=0; angle -=20){
      pwm.setPWM(1, 0, angleToPulse(angle) );
      pwm.setPWM(3, 0, angleToPulse(angle) );
      break;
    }
  }

  if(input=='B')//for vertical expansion motion of 
  {
    for( int angle =0; angle<100; angle +=20){
      pwm.setPWM(1, 0, angleToPulse(angle) );
      pwm.setPWM(3, 0, angleToPulse(angle) );
      break;
    }

    for( int angle =100; angle>=0; angle -=20){
      //delay(1000);
      pwm.setPWM(0, 0, angleToPulse(angle) );
      pwm.setPWM(2, 0, angleToPulse(angle) );
      break;
    }
  }




  if(input=='L')//for horizontal compression motion of 
  {
    for( int angle =0; angle<100; angle +=20){
      //delay(1000);
      pwm.setPWM(4, 0, angleToPulse(angle) );
      pwm.setPWM(6, 0, angleToPulse(angle) );
      break;
    }

    for( int angle =100; angle>=0; angle -=20){
      //delay(1000);
      pwm.setPWM(5, 0, angleToPulse(angle) );
      pwm.setPWM(7, 0, angleToPulse(angle) );
      break;
    }
  }

  if(input=='R')//for horizontal expansion motion of 
  {
    for( int angle =0; angle<100; angle +=20){
      //delay(1000);
      pwm.setPWM(5, 0, angleToPulse(angle) );
      pwm.setPWM(7, 0, angleToPulse(angle) );
      break;
    }

    for( int angle =100; angle>=0; angle -=10){
      //delay(1000);
      pwm.setPWM(4, 0, angleToPulse(angle) );
      pwm.setPWM(6, 0, angleToPulse(angle) );
      break;
    }
  }
//omni wheels motion code

  if(input=='G')//omni forward
 { analogWrite(ena,100);
  analogWrite(enb,100);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
} 

if (input=='H')  //omni backward
{
  analogWrite(ena,100);
  analogWrite(enb,100);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  
}


if(input=='I')  //omni left
{
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
} 

if (input=='J')  //omni right
{
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
}

  
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}