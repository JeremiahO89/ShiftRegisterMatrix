#include "BluetoothTypeConverter.h"
#include "ShiftRegister.h" //Shift Register Functinality and setup
#include "Multiplexer.h" //Multiplexer Functinality
//#include <Arduino.h>


// These are FIXED for now
const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister highRegister = ShiftRegister(12,9,10,4,11,numRows);
ShiftRegister lowRegister = ShiftRegister(8,5,6,3,7,numColumns);


// setUp the Multiplexer class
Multiplexer display = Multiplexer(highRegister, lowRegister);



String receivedData = "";
int dataCounter = 11;
int dataNum_Rows = 0;
int dataNum_Columns = 0;
int dataAction = 0;


uint8_t* hexData = nullptr;
bool* ledStates = nullptr;


void setup() {

  Serial.begin(9600);
  Serial.println("Started: ");

  lowRegister.enableOutputs();
  highRegister.enableOutputs();

  delay(2000);
  
  lowRegister.clearMemory();
  lowRegister.pushMemory();
  highRegister.highState();
  for (int i=0; i<8; i++){
    highRegister.pushState();}
  highRegister.pushMemory();
  Serial.println("All On");
  delay(1000);

  highRegister.clearMemory();
  highRegister.pushMemory();
  Serial.println("All Off");
  delay(1000);


  //should be only the top let led

  //receivedData = "00 08 08 FF 00 FF 00 FF 00 FF 00"; // should turn them all on
  receivedData = "00 08 08 FF 81 81 81 81 81 81 FF"; // should turn them all on

  hexData = decodeBluetoothStr(receivedData, dataCounter);

  for(int i = 0; i < dataCounter; i++){
    if (hexData[i] < 0x10) Serial.print("0");
    Serial.print(hexData[i], HEX);
    Serial.print(" ");
  }

  // frees the previous ledStates array if it exists
  // convert hex into usable data (allocates memory)
  ledStates = hexToBool(hexData, dataCounter, &dataAction, &dataNum_Rows, &dataNum_Columns);
  freeUnit8Array(hexData); // Done with hex Data, deallocate hexData

  for(int i = 0; i < dataNum_Rows*dataNum_Columns; i++){
    if (i%dataNum_Rows == 0){
      Serial.println("");
    }
    Serial.print(ledStates[i]);
  }

    delay(1000);

     /*we now have a pointer to an array(ledStates) of size dataCounter which has the led states */
    // display the matrix on the ouput (This only displays for a short time (less than a second))
    display.displayBoolArray(ledStates, dataCounter, dataAction, dataNum_Rows, dataNum_Columns);

    Serial.println("DONE:");
}      



void loop() {

  display.displayBoolArray(ledStates, dataCounter, dataAction, dataNum_Rows, dataNum_Columns);


}