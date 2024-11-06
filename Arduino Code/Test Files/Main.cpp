#include "BluetoothTypeConverter.h"
#include "ShiftRegister.h" //Shift Register Functinality and setup
#include "Multiplexer.h" //Multiplexer Functinality
#include <SoftwareSerial.h>
//#include <Arduino.h>

//Define the bluetooth chip
const int RX_PIN = 2; 
const int TX_PIN = 13;
SoftwareSerial bluetooth(RX_PIN, TX_PIN); 


// These are FIXED for now
const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister highRegister = ShiftRegister(12,9,10,4,11,numRows);
ShiftRegister lowRegister = ShiftRegister(8,5,6,3,7,numColumns);


// setUp the Multiplexer class
Multiplexer display = Multiplexer(highRegister, lowRegister);



void setup() {
  bluetooth.begin(9600); // set bluetooth pulling rate

}

String receivedData = "";
int dataCounter = 0;
int dataNum_Rows = 0;
int dataNum_Columns = 0;
int dataAction = 0;


uint8_t* hexData = nullptr;
bool* ledStates = nullptr;



void loop() {

  while (bluetooth.available()) {
    char incomingByte = bluetooth.read();

    if (incomingByte == '\n') {
      // pointer to hex array (allocates memory)
      hexData = decodeBluetoothStr(receivedData, dataCounter);
     
      // frees the previous ledStates array if it exists
      if (ledStates);
        freeBoolArray(ledStates);
      // convert hex into usable data (allocates memory)
      ledStates = hexToBool(hexData, dataCounter, &dataAction, &dataNum_Rows, &dataNum_Columns);
      freeUnit8Array(hexData); // Done with hex Data, deallocate hexData
     
      /*we now have a pointer to an array(ledStates) of size dataCounter which has the led states */
  
      // display the matrix on the ouput (This only diplays for a short time (less than a second))
      display.displayBoolArray(ledStates, dataCounter, dataAction, dataNum_Rows, dataNum_Columns);

      

      // clear the string after message is received
      receivedData = "";
      dataCounter = 0;
    }

    else{
      receivedData += incomingByte;
      dataCounter += 1;
    }
  }

}