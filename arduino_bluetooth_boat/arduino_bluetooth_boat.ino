#include<Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial I2CBT(10, 11); //PIN10 and PIN11 are RX and TX respectively
Servo myservo; 
int value = 90; //angle
byte cmmd;
byte cmmdpre = 0;

void setup() {
  myservo.attach(9); //servo to pin9
  Serial.begin(9600);
  I2CBT.begin(9600);
  pinMode(5, OUTPUT); //fan
  pinMode(6, OUTPUT); //fan
}

void loop() {
  if ((I2CBT.available()) > 0) {  //if arduino get a signal
    Serial.print(cmmd = char(I2CBT.read()));
    Serial.print("\n");
  }

  if (cmmd < 67) { //if arduino get the signal of turning the direction, no maatter right or left
    servee();
  } else {
    cmmdpre = cmmd;
    servee();
  }
}

void dir() {
  if (cmmd == 65) { //right
    value += 45;
  } else if (cmmd == 66) {
    value -= 45; //left
  }
  myservo.write(value);
  cmmd = 0;
}

void servee() {
  switch (cmmdpre) {
    case 67: //'C'
      analogWrite(5, 0);
      analogWrite(6, 0);
      dir();
      break;

    case 68://'D'
      analogWrite(5, 50);
      analogWrite(6, 0);
      dir();
      break;

    case 69://'E'
      analogWrite(5, 90);
      analogWrite(6, 0);
      dir();
      break;

    case 70://'F'
      analogWrite(5, 125);
      analogWrite(6, 0);
      dir();
      break;

    case 71://'G'
      analogWrite(5, 160);
      analogWrite(6, 0);
      dir();
      break;

    case 72://'H'
      analogWrite(5, 200);
      analogWrite(6, 0);
      dir();
      break;

    case 73://'I', back forward
      analogWrite(6, 150);
      analogWrite(5, 0);
  }
}
