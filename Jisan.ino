#include <Servo.h>
#include <AFMotor.h>
Servo MunnaPagla;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor Pump(3);
const int FlameRight=A15;
const int FlameFront=A14;
const int FlameLeft=A13;
const int threshold=500;
const int trigPin = 41;
const int echoPin = 43;
const int buz = 37;
int FlameR1=0;
int FlameF2=0;
int FlameL3=0;
int high=0;
int servoPos=0;
int distance=0;
int randomdir=0;
void setup() {
       MunnaPagla.write(90);
       Serial.begin(9600);
       pinMode(FlameRight,INPUT);
       pinMode(FlameFront,INPUT);
       pinMode(FlameLeft,INPUT);
       pinMode(trigPin, OUTPUT);
       pinMode(echoPin, INPUT);
       pinMode(buz, OUTPUT);
       motor1.setSpeed(255);
       motor2.setSpeed(255);
       Pump.setSpeed(255);
       MunnaPagla.attach(9);
}

void loop() {
       FlameR1=analogRead(FlameRight);
       FlameF2=analogRead(FlameFront);
       FlameL3=analogRead(FlameLeft); 
       delay(500);
       if(FlameR1>threshold||FlameF2>threshold||FlameL3>threshold){
       motor1.run(RELEASE);
       motor2.run(RELEASE);
       Serial.println("FIRE");
       detect();
       }
       distance= Distance();
       Serial.print(distance);
       Serial.println("CM");

        if (distance<=25){
         randomdir=random(2);
          if(randomdir==1){
           right();
           }else{
           left();
         }
        }else{
          go();
        }
       
       }
void detect(){
  high=max(max(FlameR1, FlameF2),FlameL3);
  Serial.println(high);
  if (FlameR1==high){
    servoPos=180;
    }else if(FlameF2==high){
      servoPos=90;
      }else if(FlameL3==high){
        servoPos=0;
        }
    Serial.println(servoPos); 
    ServoAndPump(servoPos); 
  delay (3000);
  }

  //-------------------------
  int ServoAndPump(int x){
    digitalWrite(buz,HIGH);
    MunnaPagla.write(x);
    delay(500);
    Pump.run(FORWARD);
    delay(5000);
    digitalWrite(buz,LOW);
    Pump.run(RELEASE);
    MunnaPagla.write(90);
        
    }



int Distance(){
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  return distance;
  }


void go(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);

      }
//---------------------------------------
void left(){
  Serial.print("Left Triggered");
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
 
  delay(1000);
 
  }
//---------------------------------------
void right(){
  Serial.print("Right Triggered");
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(1000);
  }
