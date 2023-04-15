#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

SoftwareSerial HC12(rxPin, txPin); //RX and TX of HC-12 module
int trigPin = 5;
int echoPin = 6;
int led_radio = 8;
int led_board = 2;
long duration;
int distance;

int LDR = A0;
int lightStatus = 0;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led_radio, OUTPUT);
  pinMode(led_board, OUTPUT);
}

void loop() {
  // digitalWrite(led_board, HIGH);
  // CheckDistance();
  // if(max_distance >= distance && distance >= min_distance){
  //   digitalWrite(led_radio, HIGH);
  //   HC12.write(230);
  //   //Serial.println("END");
  //   Serial.print("distance: ");<
  //   Serial.println(distance);
  // }else{
  //   digitalWrite(led_radio, LOW);
  // }
  digitalWrite(led_board, HIGH);
  laserCheck();
}



bool laserCheck() {

  lightStatus = analogRead(LDR);
  //Serial.println(lightStatus);
  if(lightStatus > 1000)
  {
    HC12.write(230);
    //Serial.println("Arrived!");
    // while(lightStatus < 1000){
    //   Serial.println(lightStatus);
    // }
  }else{
    HC12.write(200);
  }
  // while(lightStatus >= 1000)
  // Serial.println(lightStatus);
  // delay(500);
}
