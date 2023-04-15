// Include the library driver for display:
#include <TM1637Display.h>
#include <SoftwareSerial.h>

// Define the connections pins for display
#define CLK 6
#define DIO 7
#define rxPin 10
#define txPin 11

// Define other pin connections
//#define UP_BUTTON 2
#define RESET_BUTTON 3
#define START_BUTTON 4
#define BUZZER 9
#define LED_BOARD 2
#define LED_RADIO 12

int duration;
int code = 0;
SoftwareSerial HC12(rxPin, txPin); //RX and TX of HC-12 module
// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);

// Set the individual segments for the word displays:
//const uint8_t seg_end[] = {
//  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,         // E
//  SEG_C | SEG_E | SEG_G,                         // n 
//  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
//  0x00                                           // All off
//};
//
//const uint8_t seg_go[] = {
//  SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,// g
//  SEG_C | SEG_D | SEG_E | SEG_G,                  // o
//  0x00,                                           // All off
//  0x00                                           // All off
//};

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

  pinMode(RESET_BUTTON, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BOARD, OUTPUT);
  pinMode(LED_RADIO, OUTPUT);
  float duration = 0;              // Default to 30 seconds
  display.setBrightness(3);   // 0 to 7 change if required
}

void loop() {
  // Function will checks for time change buttons and only return 
  digitalWrite(LED_BOARD, HIGH);
  
  //CheckIfAlign();
  // when start button pressed
  WaitForStart();
  // Start the duration timer
  TimeDuration();
  //TestRadio();
}

void TestRadio(){
  //Serial.write("Read Radio");
  digitalWrite(LED_RADIO,LOW);
  if(HC12.available()){
    digitalWrite(LED_RADIO,HIGH);
    Serial.write(HC12.read());
  }

  if(Serial.available()){
    //digitalWrite(LED_RADIO,HIGH);
    HC12.write(Serial.read());
  }
}

void WaitForStart(){
  digitalWrite(LED_RADIO,LOW);
  while (digitalRead(START_BUTTON) == HIGH){
    code = 0;
    duration = 0;
    
    HC12.flush();
    HC12.end();
    HC12.begin(9600);
    
    ShowTime(duration);
  }
  // Start button has been pressed
  tone(BUZZER, 1500, 100);
  display.clear();
  //display.setSegments(seg_go);
}

void TimeDuration(){
  // While loop will continue until time up
  unsigned long startTime = millis();
  int long timer = 6000; //decimals

  // Repeatedly check if time is up
  while (duration < timer && digitalRead(RESET_BUTTON) == HIGH){

    //How the fuck I have to flush the fucking buffer
    while(HC12.available() > 0) {
      code = HC12.read();
      // Serial.println(code);
    }
    
    if(code == 230) {
      break;
      digitalWrite(LED_RADIO,LOW);
    } else if(code == 200){
      digitalWrite(LED_RADIO,HIGH);
    }
    
    // Calculate time elapsed in seconds
    duration = (millis() - startTime) / 10;
    ShowTime(duration);
  }
  
  if(duration > timer) //sometimes goes over for too much speed
    duration = timer;
  // Time up
  tone(BUZZER, 750, 250);
  display.clear();
  delay(500);  
  ShowTime(duration);
  delay(500);
  display.clear();
  delay(500);
  ShowTime(duration);
  delay(500);
  display.clear();
  delay(500);
  ShowTime(duration);
  delay(500);
  
  while(digitalRead(RESET_BUTTON) == HIGH);
  WaitForStart();
}

//decimal value
void ShowTime(int value){
//  int iDecimal = 
//  int iCentos =
//  int iSeconds = 
//  // Show on 4 digit display
//  uint16_t number = iMinutes * 100 + iSeconds;
  display.showNumberDecEx(value, 0b01000000, true, 4, 0);    
}

bool CheckIfAlign(){
  while(HC12.available() > 0) {
    code = HC12.read();
    // Serial.println(code);
  }

  if(code == 200){
    digitalWrite(LED_RADIO,HIGH);
    return true;
  }
  else{
    digitalWrite(LED_RADIO,LOW);
    return false;
  }
}
