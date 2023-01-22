#include "I2CTransfer.h"


I2CTransfer myTransfer;

#define SLAVE_ID 9

struct __attribute__((packed)) communication_object {
  char sender[3];
  char reciever[3];
  char sing;
  float amount;
  int16_t neg_v;
  int32_t ints_array[3];
};

struct communication_object testStruct;

template<typename T, size_t n>
void print_array(T const(& arr)[n])
{
    /// Function to print array of any type
    Serial.print("[");
    for (size_t i = 0; i < n; i++) {
        Serial.print(arr[i]);
        Serial.print(" ");
    }
    Serial.println("]");
}

/////////////////////////////////////////////////////////////////// Callbacks
void hi()
{
  myTransfer.rxObj(testStruct);
  Serial.println("Slave | recieve object: ");
  Serial.print("sender:");
  Serial.println(testStruct.sender);
  Serial.print("reciever:");
  Serial.println(testStruct.reciever);
  Serial.println(testStruct.sing);
  Serial.println(testStruct.amount);
  print_array(testStruct.ints_array);
  Serial.println(testStruct.neg_v);
  Serial.println("---------");
  // myTransfer.sendDatum("Response from Slave 9");
}

// supplied as a reference - persistent allocation required
const functionPtr callbackArr[] = { hi };
///////////////////////////////////////////////////////////////////

void requestEvent() {
  // IT WORKS !!!!
  int ANSWERSIZE = 10;
  String answer = "Hello12345";


  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response,sizeof(response));
  
  // Print to Serial Monitor
  Serial.println("Slave | Send respose on Master's request");
}

void setup()
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ID); // Set slave address
  Wire.onRequest(requestEvent); 
  ///////////////////////////////////////////////////////////////// Config Parameters
  configST myConfig;
  myConfig.debug        = false;
  myConfig.callbacks    = callbackArr;
  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);
  /////////////////////////////////////////////////////////////////
  
  myTransfer.begin(Wire, myConfig);
}


void loop()
{
  // Do nothing
}