#include "I2CTransfer.h"


I2CTransfer myTransfer;

#define SLAVE_ID 1

struct __attribute__((packed)) communication_object {
  char sender[3];
  char reciever[3];
  char sing;
  float amount;
};

struct communication_object testStruct;


void setup()
{
  Serial.begin(9600);
  // Wire.begin(SLAVE_ID);
  Wire.begin();

  myTransfer.begin(Wire);
  // TODO: try: struct name sara = { "Sara", "Black" };
  
  strcpy(testStruct.sender, "MS" );
  strcpy(testStruct.reciever, "S1" );
  testStruct.sing = '$';
  testStruct.amount = 4.5;
}


void loop()
{
  Serial.println("Master | Start loop ----------------");
  Serial.print("sender:");
  Serial.println(testStruct.sender);
  Serial.print("reciever:");
  Serial.println(testStruct.reciever);
  Serial.println(testStruct.sing);
  Serial.println(testStruct.amount);
  Serial.println("---------");
  int i = 0;
  while (i<=10){
    myTransfer.sendDatum(testStruct);
    delay(500);
    i++;
  }
  // Wire.end();
  // myTransfer.reset();
  // Serial.println("Master | First connection reset. Trying to send to same slave again ------");



  // Wire.begin(SLAVE_ID);
  // myTransfer.begin(Wire);
  // i = 0;
  //   while (i<=10){
  //   myTransfer.sendDatum(testStruct);
  //   delay(500);
  //   i++;
  // }
  // Serial.println("Master | Second connection reset. Sending to random slave ------");



  // Wire.begin(SLAVE_ID+1); // send to another slave
  // myTransfer.begin(Wire);
  // i = 0;
  // while (i<=10){
  //   myTransfer.sendDatum(testStruct);
  //   delay(500);
  //   i++;
  // }
  // Serial.println("Master | End loop ----------------");
}