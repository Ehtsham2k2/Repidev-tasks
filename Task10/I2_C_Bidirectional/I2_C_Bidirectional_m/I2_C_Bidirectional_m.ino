// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin();        // join I2C bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Serial.println("enter num 0--> No Operation   1--> master write  2--> slave writer");
}

byte x = 0;
int a;

void master_s() {
  // master sender slave reciever
  
  Wire.beginTransmission(8);  // transmit to device #8
  Wire.write('c');            // sends 1 bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();     // stop transmitting

  x++;
  delay(500);
}
void slave_s() {
  // slave sender and master reiever
  
  Wire.requestFrom(8, 6);  // request 6 bytes from slave device #8

  while (Wire.available()) {  // slave may send less than requested
    char c = Wire.read();     // receive a byte as character
    Serial.print(c);          // print the character
  }

  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    a = Serial.read();
    switch (a) {
      case '0':
        break;
      case '1':
        master_s();
        Serial.println("master sender slave reciever");
        break;
      case '2':
        slave_s();
        Serial.println("slave sender and master reiever");
        break;
    }
  }


  //master_s();
  //slave_s();
}
