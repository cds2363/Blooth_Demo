/*
  Bluetooth demo code.

  2016.04.11
  by kjcode j.lee
 */

#include <SoftwareSerial.h>

const int green_led_pin   = 13;
const int yellow_led_pin  = 12;
const int red_led_pin     = 11;
const int light_sensor_analog_pin  = 0;  //A0

SoftwareSerial BTSerial(8, 9); // SoftwareSerial(RX, TX)

// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(9600);
  Serial.println("Hello!");
  
  // set the data rate for the BT port
  BTSerial.begin(9600); 
  
  // initialize digital pin 13 as an output.
  pinMode(green_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);  
  pinMode(red_led_pin, OUTPUT);  
}

// the loop function runs over and over again forever
void loop() {

/*  
  //test code.
  digitalWrite(green_led_pin, HIGH);
  delay(500);            
  digitalWrite(green_led_pin, LOW);
  delay(500);           
  digitalWrite(yellow_led_pin, HIGH);
  delay(500);            
  digitalWrite(yellow_led_pin, LOW);
  delay(500);           
  digitalWrite(red_led_pin, HIGH);
  delay(500);            
  digitalWrite(red_led_pin, LOW);
  delay(500);
*/

  //bluetooth
  while (BTSerial.available()) { // if BT sends something
    byte data = BTSerial.read();
    Serial.write(data); // write it to serial(serial monitor)

    //LED点滅
    digitalWrite(green_led_pin, HIGH);
    delay(100);
    digitalWrite(green_led_pin, LOW);
  }

  //Ligit sensor
  int brightness = analogRead(light_sensor_analog_pin);
  int intensity = map(brightness, 0,1023,255,0);  //0-1023 -> 255-0
  Serial.write(intensity);
  
  //red led brightness update
  analogWrite(red_led_pin, intensity);

  //send bluetooth
  BTSerial.write(intensity); // write it to BT

/*  
  while (Serial.available()) { // if Serial has input(from serial monitor)
    byte data = Serial.read();
    BTSerial.write(data); // write it to BT
    
    //LED点滅
    digitalWrite(yellow_led_pin, HIGH);
    delay(100);
    digitalWrite(yellow_led_pin, LOW);
  }
*/
  
  // wait.
  delay(100);
}
