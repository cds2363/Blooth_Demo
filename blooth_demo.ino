/*
  Bluetooth demo code.

  2016.04.11
  by kjcode j.lee
 */

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 4); // SoftwareSerial(RX, TX)

//pin define
const int green_led_pin   = 11;
const int orange_led_pin  = 12;
const int red_led_pin     = 13;
const int light_sensor_analog_pin  = A0;


//Bluetooth command define
typedef enum ColorType {
  ColorTypeNone            = 0,
  ColorTypeRed             = 1 << 0,
  ColorTypeGreen           = 1 << 1,
  ColorTypeOrange          = 1 << 2,
  ColorTypeRedAndGreen     = 1 << 3,
  ColorTypeRedAndOrange    = 1 << 4,
  ColorTypeGreenAndOrange  = 1 << 5,
  ColorTypeOrangeAndGreen  = 1 << 6,
  ColorTypeAll             = 1 << 7,
};


// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(9600);
  Serial.println("Hello KJCode!");
  
  // set the data rate for the BT port
  BTSerial.begin(9600); 
  
  // initialize digital pin 13 as an output.
  pinMode(green_led_pin, OUTPUT);
  pinMode(orange_led_pin, OUTPUT);  
  pinMode(red_led_pin, OUTPUT);  
 
}

// the loop function runs over and over again forever
void loop() {
  
  //test code.
//  digitalWrite(green_led_pin, HIGH);
//  delay(500);            
//  digitalWrite(green_led_pin, LOW);
//  delay(500);           
//  digitalWrite(orange_led_pin, HIGH);
//  delay(500);            
//  digitalWrite(orange_led_pin, LOW);
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

    if(iphone_command & ColorTypeRed) {
      digitalWrite(red_led_pin, HIGH);
      digitalWrite(green_led_pin, LOW);
      digitalWrite(orange_led_pin, LOW);

    }else if(iphone_command & ColorTypeGreen) {
      digitalWrite(red_led_pin, LOW);
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(orange_led_pin, LOW);

    }else if(iphone_command & ColorTypeOrange) {
      digitalWrite(red_led_pin, LOW);
      digitalWrite(green_led_pin, LOW);
      digitalWrite(orange_led_pin, HIGH);

    }else if(iphone_command & ColorTypeRedAndGreen) {
      digitalWrite(red_led_pin, HIGH);
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(orange_led_pin, LOW);

    }else if(iphone_command & ColorTypeRedAndOrange) {
      digitalWrite(red_led_pin, HIGH);
      digitalWrite(green_led_pin, LOW);
      digitalWrite(orange_led_pin, HIGH);

    }else if(iphone_command & ColorTypeGreenAndOrange) {
      digitalWrite(red_led_pin, LOW);
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(orange_led_pin, HIGH);

    }else if(iphone_command & ColorTypeOrangeAndGreen) {
      digitalWrite(red_led_pin, LOW);
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(orange_led_pin, HIGH);
      
    }else if(iphone_command & ColorTypeAll) {
      digitalWrite(red_led_pin, HIGH);
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(orange_led_pin, HIGH);
    }else {
        ledOff();
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
//    digitalWrite(orange_led_pin, HIGH);
//    delay(100);
//    digitalWrite(orange_led_pin, LOW);
//  }

  // wait.
  delay(100);
}

void ledOff() {
  digitalWrite(green_led_pin, LOW);   
  digitalWrite(green_led_pin, LOW); 
  digitalWrite(orange_led_pin, LOW);
}
