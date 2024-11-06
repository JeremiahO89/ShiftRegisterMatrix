#include "BluetoothTypeConverter.h"

int action;
int num_Rows;
int num_Columns;

String inputData = "010404AA"; // Example data
int inputDataLen = 4;

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);

    // Call the decodeBluetooth function
    uint8_t* validData = decodeBluetoothStr(inputData, inputDataLen);
    // Your hexToBool function should return a boolean array or whatever you need
    bool* output = hexToBool(validData, inputDataLen, &action, &num_Rows, &num_Columns);

    // Check if decoding was successful
    if (output != nullptr) {
        // Output the result
        Serial.print("Action: ");
        Serial.println(action);
        Serial.print("Rows: ");
        Serial.println(num_Rows);
        Serial.print("Columns: ");
        Serial.println(num_Columns);
        Serial.println("LED States (Matrix):");

        // Print the decoded LED states as a matrix
        for (int row = 0; row < num_Rows; ++row) {
            for (int col = 0; col < num_Columns; ++col) {
                Serial.print(output[row * num_Columns + col]);
                Serial.print(" ");  // Print each bit in matrix format
            }
            Serial.println();  // Newline for next row
        }

        // Free the allocated memory for output if using dynamic allocation
        free(output);
    } else {
        Serial.println("Decoding failed or invalid data provided.");
    }
}

void loop() {
    // Your main logic can go here
}

