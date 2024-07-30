// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.



/* master sends slave reads and then slave sends and master recieves*/

#include <Wire.h>
#include<string.h>
int on_r =0 ;
//char word[];
void setup() {
  Wire.begin(8);                // join I2C bus with address #8
  Wire.onReceive(receiveEvent); // register event

  Wire.onRequest(requestEvent); // register event

  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}
// master is sender & slave reciever
// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character

    if (c=='c'){
       on_r =1;
     }
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
void requestEvent() {
  switch(on_r){
    case 1:
     Wire.write("hello "); // respond with message of 6 bytes
      // as expected by master
      break;
    case 0:
     Wire.write("NOT "); // respond with message of 6 bytes
      // as expected by master
      break;


  }
 
}
