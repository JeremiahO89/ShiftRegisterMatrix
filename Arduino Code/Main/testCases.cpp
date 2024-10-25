#include "BluetoothTypeConverter.h"
#include <stdint.h>
#include <iostream> // For printing the output
#include <cstdlib>  // For free()

int action;
int num_Rows;
int num_Columns;

int main() {
    uint8_t validData[] = {0x01, 0x04, 0x04, 0xAA}; // Example data
//1010
//1010
    // Call the decodeBluetooth function
    bool* output = decodeBluetooth(validData, sizeof(validData), &action, &num_Rows, &num_Columns);

    // Check if decoding was successful
    if (output != nullptr) {
        // Output the result
        std::cout << "Action: " << action << std::endl;
        std::cout << "Rows: " << num_Rows << std::endl;
        std::cout << "Columns: " << num_Columns << std::endl;

        // Print the decoded LED states as a matrix
        std::cout << "LED States (Matrix): " << std::endl;
        for (int row = 0; row < num_Rows; ++row) {
            for (int col = 0; col < num_Columns; ++col) {
                std::cout << output[row * num_Columns + col] << " ";  // Print each bit in matrix format
            }
            std::cout << std::endl;  // Newline for next row
        }

        // Free the allocated memory for output
        free(output);
    } else {
        std::cout << "Decoding failed or invalid data provided." << std::endl;
    }

    return 0;
}
