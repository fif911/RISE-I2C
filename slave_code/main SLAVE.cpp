/*
  I2C Slave Demo
  i2c-slave-demo.ino
  Demonstrate use of I2C bus
  Slave receives character from Master and responds
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include Arduino Wire library for I2C
#include "Arduino.h"
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define Slave answer size
#define ANSWERSIZE 5

// Define string with response to Master
String answer = "Hello";


void receiveEvent(int byteCount) {
    // byte x;
    
    Serial.print("Receive event. Byte count: ");
    Serial.println(byteCount);

    // Read while data received
    while (0 < Wire.available()) {
        byte x = Wire.read();
        Serial.print("Value read: ");
        Serial.println(x);

    }
    
    // Print to Serial Monitor
    // Serial.print("Receive event. Value read: ");
    
    // Serial.print("; Byte count: ");
    
}

void requestEvent() {

  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response,sizeof(response));
  
  // Print to Serial Monitor
  Serial.println("Request event");
}


void setup() {

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);
  
  // Function to run when data requested from master
  Wire.onRequest(requestEvent); 
  
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  
  // Setup Serial Monitor 
  Serial.begin(9600);
  Serial.println("I2C Slave Demonstration");
}

void loop() {

  // Time delay in loop
  delay(50);
  Serial.print(".");
}
