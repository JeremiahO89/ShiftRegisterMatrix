#include "BluetoothTypeConverter.h"

/* PACKET FORMAT:
    First byte (8 bits): preform (what to do)
    Second byte (8 bits): number of rows
    Third byte (8 bits): number of columns
    REST bytes = #rows * #columns / 8

*/

uint8_t* decodeBluetoothStr(String dataString, int dataStringLen){
    /*
    Input: 
    dataString a String of hex values separated by spaces
    dataStringLen: the number of hex values in the string
    Output: 
    Array of hex values
    Purpose: Turn a String of HEX into an Array
    */

   // Allocate memory for output Array
    uint8_t* outputArray = (uint8_t*)malloc(dataStringLen * sizeof(uint8_t));
    if (outputArray == nullptr) {
        return nullptr; // Memory allocation failed
    }

    // loop though number of hex characters
    for (int i = 0; i<dataStringLen; i++){
        // Add HEX valued into array while skipping over every 3rd index as that is a space
        outputArray[i] = charToHex(dataString[i*3],dataString[i*3+1]);
    }
    return outputArray;
}

void freeUnit8Array(uint8_t* array){
    free(array);
}

uint8_t charToHex(char highValue, char lowValue){
    /*
    Input: 2 char values from either "0"-"9" and "A"-"F"
    Output: Return the Hex value of the two in the form (highValue)(lowValue)
    Example: input "A" "9" returns HEX A9
    */
   uint8_t highValueInt = 0;
   uint8_t lowValueInt = 0;

   if ( '0' <= highValue && highValue <= '9'){highValueInt = highValue - '0';}
   else if('A' <= highValue && highValue <= 'F'){highValueInt = highValue - 'A' + 10;}

   if ( '0' <= lowValue && lowValue <= '9'){lowValueInt = lowValue- '0';}
   else if('A' <= lowValue && lowValue <= 'F'){lowValueInt = lowValue - 'A' + 10;}
   
   //combine the two values into one HEX
   return (highValueInt<<4) | lowValueInt;
}

bool* hexToBool(uint8_t* bluetoothData, int bluetoothDataSize, int* action, int* num_Rows, int* num_columns) {
    /* 
    Input: 
        uint8_t* bluetoothData : an array of hex values
        int bluetoothDataSize: size of the hex values array, starts at 1 
        int* num_Rows: pointer to store the number of rows in the return array
        int* num_columns: pointer to store the number of columns in the return array
    4
    Output: return a pointer to an array of size (num_Rows * num_Columns) of bool's
    ^^ these bool's will be the state of the LED
    
    Purpose: convert a HEX array to binary, Identify action, and #rows/#columns
    */
    
    // Check if there are enough bytes in bluetoothData
    if (bluetoothDataSize == 1) { // There was only one bit
        *action = bluetoothData[0];
        return nullptr; 
    }
    else if (bluetoothDataSize < 3) { // Missing row and column data
        *action = 0;
        return nullptr;
    }

    // Get the action and the # of rows/columns, HEX will type cast to int
    *action = bluetoothData[0]; 
    *num_Rows = bluetoothData[1];
    *num_columns = bluetoothData[2];

    // Calculate number of byte's left to read. (Number of HEX values left)
    int totalSize = (*num_Rows) * (*num_columns) / 8;


    // Allocate memory for output array
    bool* outputArray = (bool*)malloc(totalSize * 8 * sizeof(bool));
    if (outputArray == nullptr) {
        return nullptr; // Memory allocation failed
    }

    // Fill the outputArray
    for (int bytesLeft = 0; bytesLeft < totalSize; ++bytesLeft) {

        // Check if there is data available to read
        if (bytesLeft + 3 < bluetoothDataSize) { // add 3 to exclude the 3 data bits in the beginning
            // Hex value to read
            uint8_t hexValue = bluetoothData[bytesLeft + 3];

            // Add the bits into the memory from left to right from the HEX value
            for(int bitCount = 0; bitCount < 8; ++bitCount){
                outputArray[bytesLeft * 8 + bitCount] = (hexValue >> (7-bitCount)) & 1;
            }

        } else {
            // fill the rest with 0's
             for(int bitCount = 0; bitCount < 8; ++bitCount){
                outputArray[bytesLeft * 8 + bitCount] = false;
            }
        }
    }
    return outputArray; // Return pointer to bool array
}

void freeBoolArray(bool* array) {
    free(array);
}
