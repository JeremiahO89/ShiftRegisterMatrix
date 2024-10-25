#include "BluetoothTypeConverter.h"
#include <stdint.h> // for HEX values
#include <cstdlib> // for malloc and free

/* PACKET FORMAT:
    First byte (8 bits): preform (what to do)
    Second byte (8 bits): number of rows
    Third byte (8 bits): number of columns
    REST bytes = #rows * #columns / 8

*/

bool* decodeBluetooth(uint8_t* bluetoothData, int bluetoothDataSize, int* action, int* num_Rows, int* num_columns) {
    /* 
    Input: 
        uint8_t* bluetoothData : an array of hex values
        int bluetoothDataSize: size of the hex values array, starts at 1 
        int* num_Rows: pointer to store the number of rows in the return array
        int* num_columns: pointer to store the number of columns in the return array
    4
    Output: return a pointer to an array of size (num_Rows * num_Columns) of bool's
    ^^ these bool's will be the state of the LED
    
    Purpose: convert a HEX array to binary
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

    // Get the action and the # of LED rows and columns, HEX will type cast to int
    *action = bluetoothData[0]; 
    *num_Rows = bluetoothData[1];
    *num_columns = bluetoothData[2];

    // Calculate number of byte's left to read. (Number of HEX values left)
    int totalSize = (*num_Rows) * (*num_columns) / 8;



    // Allocate memory for the output array
    bool* outputArray = (bool*)malloc(totalSize * 8 * sizeof(bool));
    if (outputArray == nullptr) {
        return nullptr; // Memory allocation failed
    }

    // Fill the outputArray
    for (int bytesLeft = 0; bytesLeft < totalSize; ++bytesLeft) {

        // Check if there is data available to read
        if (bytesLeft + 3 < bluetoothDataSize) { // add 3 to exclude the 3 data bits in the beginning
            // Hex value
            uint8_t hexValue = bluetoothData[bytesLeft + 3];

            // Add the bits into the memory from left to right from the HEX value
            for(int bitCount = 0; bitCount < 8; ++bitCount){
                //FIXME: I'm not sure if this is right
                outputArray[bytesLeft * 8 + bitCount] = (hexValue >> (7-bitCount)) & 1;
            }

        } else {
            // fill the rest with false
             for(int bitCount = 0; bitCount < 8; ++bitCount){
                outputArray[bytesLeft * 8 + bitCount] = false;
            }
        }
    }
    return outputArray; // Return pointer to the bool array
}

void freeDecodedArray(bool* array) {
    free(array); // Function to free allocated memory for the boolean array
}
