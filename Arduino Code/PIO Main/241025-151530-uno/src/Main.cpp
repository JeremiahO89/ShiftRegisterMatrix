#include "BluetoothTypeConverter.h"
#include "ShiftRegister.h" //Shift Register Functinality and setup
#include "Multiplexer.h" //Multiplexer Functinality
#include <Arduino.h>


// These are FIXED for now
const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister highRegister = ShiftRegister(12,9,10,4,11,numRows);
ShiftRegister lowRegister = ShiftRegister(8,5,6,3,7,numColumns);


// setUp the Multiplexer class
Multiplexer display = Multiplexer(highRegister, lowRegister);



String receivedData = "";
int dataCounter = 27;
int dataNum_Rows = 0;
int dataNum_Columns = 0;
int statesSize = (dataCounter-3) * 8;
int dataAction = 0;


uint8_t* hexData = nullptr;
bool* ledStates = nullptr;

void startUP(){
  lowRegister.enableOutputs();
  highRegister.enableOutputs();
  lowRegister.clearMemory();
  lowRegister.pushMemory();
  highRegister.highState();
  for (int i=0; i<8; i++){
  highRegister.pushState();}
  highRegister.pushMemory();
  Serial.println("All On");
  delay(500);
  highRegister.clearMemory();
  highRegister.pushMemory();
  Serial.println("All Off");
  delay(250);
}

void printHEXArray(uint8_t* array, int dataCounter){
    for(int i = 0; i < dataCounter; i++){
    if (hexData[i] < 0x10) Serial.print("0");
    Serial.print(hexData[i], HEX);
    Serial.print(" ");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Started: ");

  startUP();

  //receivedData = "01 08 08 FF 81 81 81 81 81 81 FF";
  //receivedData = "01 08 10 FF 00 83 00 81 00 81 00 81 00 81 00 E1 00 FF 00";
  //receivedData = "01 08 10 FF 18 83 18 81 18 81 FF 81 18 81 18 E1 18 FF 18";
  receivedData = "01 08 18 00 FF 00 00 83 00 00 81 00 00 81 00 00 81 00 00 81 00 00 E1 00 00 FF 00";
  hexData = decodeBluetoothStr(receivedData, dataCounter);
  //printHEXArray(hexData, dataCounter);

  // frees the previous ledStates array if it exists
  // convert hex into usable data (allocates memory)
  ledStates = hexToBool(hexData, dataCounter, &dataAction, &dataNum_Rows, &dataNum_Columns);
  freeUnit8Array(hexData); // Done with hex Data, deallocate hexData
  //printBoolArray(ledStates,dataNum_Rows,dataNum_Columns);
}      



void loop() {
  display.sendData(ledStates, statesSize, dataNum_Rows, 4);
}