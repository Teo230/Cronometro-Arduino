#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11
SoftwareSerial HC12(rxPin, txPin); //RX and TX of HC-12 module
int trigPin = 5;
int echoPin = 6;
int led = 8;
int min_distance = 10;
int max_distance = 60;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  CheckDistance();
  if(max_distance >= distance && distance >= min_distance){
    digitalWrite(led, HIGH);
    HC12.write(230);
    //Serial.println("END");
    Serial.print("distance: ");
    Serial.println(distance);
  }else{
    digitalWrite(led, LOW);
  }
}

void CheckDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
//  Serial.print("distance: ");
//  Serial.println(distance);
}
