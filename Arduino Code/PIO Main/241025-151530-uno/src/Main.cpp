#include "BluetoothTypeConverter.h"
#include "ShiftRegister.h" //Shift Register Functinality and setup
#include "Multiplex.h" //Multiplexer Functinality
#include <SoftwareSerial.h>
//#include <Arduino.h>

//Define the bluetooth chip
const int RX_PIN = 1; 
const int TX_PIN = 2;
SoftwareSerial bluetooth(RX_PIN, TX_PIN); 


// These are FIXED for now
const int numRows = 8;
const int numColumns = 8;
// Use 4 different pins which will result in 8 outputs
ShiftRegister HighRegister(3,4,5,6,7,numRows);
ShiftRegister LowRegister(8,9,10,11,12,numColumns);



void setup() {
  bluetooth.begin(9600); // set bluetooth pulling rate

}

String receivedData = "";
int dataCounter = 0;
int dataNum_Rows = 0;
int dataNum_Columns = 0;
int dataAction = 0;


void loop() {

  while (bluetooth.available()) {
    char incomingByte = bluetooth.read();
    if (incomingByte == '\n') {
      
      // pointer to hex array (allocates memory)
      uint8_t* hexData = decodeBluetoothStr(receivedData, dataCounter);
      // convert hex into usable data (allocates memory)
      bool* ledStates = hexToBool(hexData, dataCounter, &dataAction, &dataNum_Rows, &dataNum_Columns);
      freeUnit8Array(hexData); // (deallocate hexData)
      /*we now have a pointer to an array(ledStates) of size dataCounter which has the led states */




    
    }

    else{
      receivedData += incomingByte;
      dataCounter += 1;
    }
  }

  // clear the string after message is received
  receivedData = "";
  dataCounter = 0;
}