#include <Servo.h>
#define motor1EnablePin 3
#define motor1_1 2
#define motor1_2 4
int motor_control=9;

int ledPin = 6;
int buttonApin = 12;
int buttonBpin = 13;
int potPin = 0;

Servo servo;
bool onoff = false;
void setup()
{
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
 // analogWrite(motor1EnablePin, 10);
   servo.attach(motor_control);
 Serial.begin(9600);
  pinMode(5,OUTPUT); // 센서 Trig 핀
  pinMode(11,INPUT); // 센서 Echo 핀
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP); 
  pinMode(buttonBpin, INPUT_PULLUP);  
}
int i=0;
void loop()
{
  long cm;
  //int sensorValue = analogRead(A0);
  int sped;
  if (digitalRead(buttonApin) == HIGH)
  {
    if(onoff){
      onoff=false;
      Serial.println("OFF222");

    } else {
      onoff=true;
      Serial.println("ON222");

    }
    delay(1000);
  }
  
  if(onoff){ //onbutton
      int speed = analogRead(potPin) / 4;
      Serial.print("loop");
      Serial.println("ON");
      digitalWrite(ledPin, HIGH);
      
      cm = distance();
     
       if(cm<20){
          Serial.println("on");
    
      digitalWrite(motor1_1, HIGH);
      digitalWrite(motor1_2, LOW);  
      if(speed>=255){
         analogWrite(motor1EnablePin, 255);
      } else if(speed<=80){
         analogWrite(motor1EnablePin, 80);

      }else {
          analogWrite(motor1EnablePin, speed);

      }
      
      Serial.print(speed);
             // analogWrite(motor1EnablePin, 1023);

      } else {
        if(i==180){
          i=-10;
        }
        i+=10;
        
        servo.write(i);
    
        Serial.println("off");
    
        analogWrite(motor1EnablePin, 0);
    
      }
      delay(1000);
  }
  else {
    Serial.println("OFF");
    digitalWrite(ledPin, LOW);

     analogWrite(motor1EnablePin, 0);
  }
  delay(100);
}

long distance() {
  long duration, cm;

  digitalWrite(5,HIGH); // 센서에 Trig 신호 입력
  delayMicroseconds(10); // 10us 정도 유지
  digitalWrite(5,LOW); // Trig 신호 off

  duration = pulseIn(11,HIGH); // Echo pin: HIGH->Low 간격을 측정
  cm = duration / 29 / 2;; // 거리(cm)로 변환

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  return cm;
}

