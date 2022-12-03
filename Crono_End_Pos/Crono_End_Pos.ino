#include <SoftwareSerial.h>
SoftwareSerial radio(0, 1); //RX and TX of HC-12 module
int trigPin = 5;
int echoPin = 6;
int min_distance = 10;
int max_distance = 60;
long duration;
int distance;
void setup() {
  Serial.begin(9600);
  radio.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  CheckDistance();
  if(max_distance >= distance && distance >= min_distance){
    radio.println("MFA#END#MFA");
    //Serial.println("END");
    Serial.print("distance: ");
    Serial.println(distance);
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
