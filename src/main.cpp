#include "I2CTransfer.h"


I2CTransfer myTransfer;

// Define Slave I2C Address
#define SLAVE_ADDR 9

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


void setup()
{
  Serial.begin(9600);
  Wire.begin(); // Master does not specify address

  myTransfer.begin(Wire);
  // TODO: structs can be constructed like: <struct object> <instance name> = { "Sara", "Black" };
  
  strcpy(testStruct.sender, "MS" );
  sprintf(testStruct.reciever, "S%d", SLAVE_ADDR);
  // strcpy(testStruct.reciever, "S1" );
  testStruct.sing = '$';
  testStruct.amount = 4.5;
  int32_t ints[3] = {INT_FAST32_MAX, INT_FAST32_MIN, 0}; // maximum possible value, minimum possible value and 0
  memcpy(&testStruct.ints_array, &ints, sizeof(testStruct.ints_array));
  testStruct.neg_v = INT_FAST16_MIN; 
}


void loop()
{
  Serial.println("Master | Object to send:");
  Serial.print("sender: ");
  Serial.println(testStruct.sender);
  Serial.print("reciever: ");
  Serial.println(testStruct.reciever);
  Serial.println(testStruct.sing);
  Serial.println(testStruct.amount);
  print_array(testStruct.ints_array);
  Serial.println(testStruct.neg_v);
  Serial.println("---------");
  
  // ----------- MASTER SENDS DATA
  myTransfer.sendDatum(testStruct, 0, SLAVE_ADDR); // Send what we want to recieve
  delay(10);

  // ----------- MASTER REQUESTS DATA

  // TODO: Request response from the slave
  Wire.requestFrom(SLAVE_ADDR, 10);

  // Add characters to string
  // TODO: Logic to recieve objects
  String response = "";
  while (Wire.available())
  {
    char b = Wire.read();
    response += b;
  } 
  // Print to Serial Monitor
  Serial.print("Master | Response from slave: '");
  Serial.print(response);
  Serial.println("'");
  Serial.println("----------------------");

  delay(500);

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