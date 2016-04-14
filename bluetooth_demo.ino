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

#define LED_ON  255
#define LED_OFF 0

//Bluetooth command define
typedef enum CommandType {
  TypeNone            = 0,
  TypeRed             = 1 << 0,
  TypeGreen           = 1 << 1,
  TypeOrange          = 1 << 2,
  TypeBlink           = 1 << 3,  
};

//
int red_onoff = LOW;
int green_onoff = LOW;
int orange_onoff = LOW;

bool blink_flag = false;

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

  int iphone_command;

  //bluetooth
  while (BTSerial.available()) { // if BT sends something
    byte data = BTSerial.read();
    //Serial.write(data); // write it to serial(serial monitor)
    //Serial.println(data);
    
    iphone_command = (int)data;
    Serial.println(iphone_command);

    blink_flag = (iphone_command & TypeBlink);

    red_onoff     = (iphone_command & TypeRed)    ?HIGH:LOW;
    green_onoff   = (iphone_command & TypeGreen)  ?HIGH:LOW;
    orange_onoff  = (iphone_command & TypeOrange) ?HIGH:LOW;
  }


  if (blink_flag) {
      if (red_onoff) {
          flashLed(red_led_pin);
      }else {
          ledOff(red_led_pin);
      }

      if (green_onoff) {
          flashLed(green_led_pin);
      }else {
          ledOff(green_led_pin);
      }

      if (orange_onoff) {
          flashLed(orange_led_pin);
      }else {
          ledOff(orange_led_pin);
      }

    }else {
      digitalWrite(red_led_pin, red_onoff);
      digitalWrite(green_led_pin, green_onoff);
      digitalWrite(orange_led_pin, orange_onoff);
    }

  //Ligit sensor
  int brightness = analogRead(light_sensor_analog_pin);
  int intensity = map(brightness, 0,1023,LED_ON,LED_OFF);  //0-1023 -> 255-0
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

void ledOnOff(bool on) {

  int flag = on?LED_ON:LED_OFF;

  digitalWrite(green_led_pin, flag);   
  digitalWrite(green_led_pin, flag); 
  digitalWrite(orange_led_pin, flag);
}

void ledOff(int pin_no) {
  digitalWrite(pin_no, LOW);
}

void flashLed(int pin_no) {
  
  //反転する
  int onoff_status = digitalRead(pin_no)==LED_OFF?LED_ON:LED_OFF;
  digitalWrite(pin_no, onoff_status);
}
