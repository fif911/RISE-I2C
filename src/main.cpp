/*
  I2C Master Demo
  i2c-master-demo.ino
  Demonstrate use of I2C bus
  Master sends character and gets reply from Slave
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

#define ESTABLISH_CONNECTIO_CMD 2003

#define ESTABLISH_CONNECTION "not_connected"
#define READY_TO_ACCEPCT_COMMANDS "ready"

String state = ESTABLISH_CONNECTION;
byte byteArray[5] = {0x12, 0x34, 0x56, 0x78, 0x35}; // 
int intArray[5] = {0, 123, 1245, 9001, 1}; // it is hard to send int array as lib supports only bytes. 
// Idea: always send 1 control byte of type, and then the values. In such way we can send arrays of ints
// TODO: There should be some ready solutions for communications but I could nt find something meaningful
// https://github.com/madsci1016/Arduino-EasyTransfer
// https://tasnemulhasannehal.wixsite.com/diary/post/sending-float-data-i2c-bus
// https://tasnemulhasannehal.wixsite.com/diary/post/sending-receiving-float-data-i2c-bus

// int len(byte array){}


int send_i2c(int slave_addr, int data[], int size)
{
  /* Send int array */

  Serial.println("Sending INT array");
  // Serial.println(data);

  // Size calculation return 2 when array is 5. Is fixed by passing size explicitly
  // Serial.println(sizeof(data));
  // Serial.println(sizeof(data[0]));
  // Serial.println( sizeof(data)/sizeof(data[0])); 

  // int size = sizeof(data)/sizeof(data[0]);
  // Serial.print("data_size: ");Serial.println(data_size);
  // uint8_t data_pointer = *data;

  Wire.beginTransmission(slave_addr);
  
  // My analougue of the overload :)
  for (int i = 0; i < 5; i++)
  {
    Serial.print(data[i]);
    Serial.print(" ");
    Wire.write(data[i]);
  }
  Serial.println("");
  Wire.endTransmission();
  return 1;
}


int send_i2c(int slave_addr, byte data[], int size)
{
  /* Send byte array */

  Serial.println("Sending BYTE array");
  // Serial.println(data);

  // Size calculation return 2 when array is 5. Is fixed by passing size explicitly
  // Serial.println(sizeof(data));
  // Serial.println(sizeof(data[0]));
  // Serial.println( sizeof(data)/sizeof(data[0])); 

  // int size = sizeof(data)/sizeof(data[0]);
  // Serial.print("data_size: ");Serial.println(data_size);
  // uint8_t data_pointer = *data;

  Wire.beginTransmission(slave_addr);
  Wire.write(data, size); // There is already an overload for passing arrays
  
  // My analougue of the overload :)
  // for (int i = 0; i < 5; i++)
  // {
  //   Serial.print(data[i]);
  //   Serial.print(" ");
  //   Wire.write(data[i]);
  // }
  // Serial.println("");
  Wire.endTransmission();
  return 1;
}

int send_i2c(int slave_addr, byte data)
{
  /* Send byte value (e.g. command)*/

  //  Write a charatre to the Slave
  Serial.println("Sending SCALAR value");
  Wire.beginTransmission(slave_addr);
  Wire.write(data);
  Wire.endTransmission();
  return 1;
}

void setup()
{

  // Initialize I2C communications as Master
  Wire.begin();

  // Setup serial monitor
  Serial.begin(9600);
  Serial.println("I2C Master Demonstration");
}

void loop()
{
  delay(1000);
  Serial.println("Write data to slave");

  // Write a charatre to the Slave
  // send_i2c(SLAVE_ADDR, *dataArray, 5);
  send_i2c(SLAVE_ADDR, byteArray, sizeof(byteArray)/sizeof(byteArray[0])); // pass pointer to the array and its size
  send_i2c(SLAVE_ADDR, intArray, sizeof(intArray)/sizeof(intArray[0])); // pass pointer to the array and its size

  Serial.println("Going to receive data");

  // Read response from Slave
  // Read back 5 characters
  Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);

  // Add characters to string
  String response = "";
  while (Wire.available())
  {
    char b = Wire.read();
    response += b;
  }

  // Print to Serial Monitor
  Serial.print("Response: '");
  Serial.print(response);
  Serial.println("'");
}