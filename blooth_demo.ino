/*
  Bluetooth demo code.

  2016.04.11
  by kjcode j.lee
 */

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 4); // SoftwareSerial(RX, TX)

//pin define
const int green_led_pin   = 11;
const int yellow_led_pin  = 12;
const int red_led_pin     = 13;
const int light_sensor_analog_pin  = A0;


//Bluetooth command define
/*
 * typedef NS_OPTIONS(NSInteger, ColorType) {
 TypeNone = 0,
 TypeRed  = 1 << 0,
 TypeGreen = 1 << 1,
 TypeYello = 1 << 2,
};
 */




// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(9600);
  Serial.println("Hello KJCode!");
  
  // set the data rate for the BT port
  BTSerial.begin(9600); 
  
  // initialize digital pin 13 as an output.
  pinMode(green_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);  
  pinMode(red_led_pin, OUTPUT);  
 
}

// the loop function runs over and over again forever
void loop() {
  
  //test code.
//  digitalWrite(green_led_pin, HIGH);
//  delay(500);            
//  digitalWrite(green_led_pin, LOW);
//  delay(500);           
//  digitalWrite(yellow_led_pin, HIGH);
//  delay(500);            
//  digitalWrite(yellow_led_pin, LOW);
//  delay(500);           
//  digitalWrite(red_led_pin, HIGH);
//  delay(500);            
//  digitalWrite(red_led_pin, LOW);
//  delay(500);

  //bluetooth
  while (BTSerial.available()) { // if BT sends something
    byte data = BTSerial.read();
    //Serial.write(data); // write it to serial(serial monitor)
    Serial.println(data);
    
    int iphone_command = (int)data;
    Serial.println(iphone_command);

    if(iphone_command == 1) {
      digitalWrite(green_led_pin, LOW);
      digitalWrite(yellow_led_pin, LOW);
      digitalWrite(red_led_pin, HIGH);
    }else if(iphone_command == 2) {
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(yellow_led_pin, LOW);
      digitalWrite(red_led_pin, LOW);
    }else if(iphone_command == 4) {
      digitalWrite(green_led_pin, LOW);
      digitalWrite(yellow_led_pin, HIGH);
      digitalWrite(red_led_pin, LOW);
    }else {
      digitalWrite(green_led_pin, LOW);
      digitalWrite(yellow_led_pin, LOW);
      digitalWrite(red_led_pin, LOW);
    }
    
/*
    //LED点滅
    digitalWrite(green_led_pin, HIGH);
    delay(100);
    digitalWrite(green_led_pin, LOW);
*/    
  }

  //Ligit sensor
  int brightness = analogRead(light_sensor_analog_pin);
  int intensity = map(brightness, 0,1023,255,0);  //0-1023 -> 255-0
//  Serial.println(intensity);
  
//  //red led brightness update
//  analogWrite(green_led_pin, intensity);

  //send bluetooth
  BTSerial.write(intensity); // write it to BT

//  while (Serial.available()) { // if Serial has input(from serial monitor)
//    byte data = Serial.read();
//    BTSerial.write(data); // write it to BT
//    
//    //LED点滅
//    digitalWrite(yellow_led_pin, HIGH);
//    delay(100);
//    digitalWrite(yellow_led_pin, LOW);
//  }

  // wait.
  delay(100);
}
