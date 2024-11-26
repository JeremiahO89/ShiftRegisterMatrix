#include "Multiplexer.h"
#include "ShiftRegister.h"
#include <Arduino.h>

# define CYCLE_TIME_ON 2 //1.5 millisecond
Multiplexer::Multiplexer(ShiftRegister& highRegister, ShiftRegister& lowRegister): _highRegister(highRegister), _lowRegister(lowRegister){
    _displaySize = _highRegister._num_outputs * _lowRegister._num_outputs;
    _displayArray = (bool*)calloc(_displaySize, sizeof(bool));
    _startColumn = 0;

}


void grabArraySection(bool* displayArray, int displayLength, bool* inputArray, int inputLength, int numRows, int startColumn){
    int displayColumns = displayLength/numRows; //8
    int inputColumns = inputLength/numRows; // 8
    for (int row = 0; row < numRows; row++){
        memcpy(&displayArray[displayColumns * row], &inputArray[row * inputColumns + startColumn], displayColumns * sizeof(bool));
    }
}

void rightShiftArray(bool* displayArray, int displayLength, bool* inputArray, int inputLength, int numRows, int *startColumn){
    // if (*startColumn > 0) { // Prevent over-shifting
    //     (*startColumn)--;
    // }
    if (*startColumn <=0) { // Prevent over-shifting
        (*startColumn) = (inputLength / numRows) - (displayLength / numRows) - 1 ;
    }
    grabArraySection(displayArray, displayLength, inputArray, inputLength, numRows, *startColumn);
    (*startColumn)--;
}

void leftShiftArray(bool* displayArray, int displayLength, bool* inputArray, int inputLength, int numRows, int *startColumn){
    // if (*startColumn < (inputLength / numRows) - (displayLength / numRows)) { // Prevent over-shifting
    //     (*startColumn)++;
    // }
    if (*startColumn >= (inputLength / numRows) - (displayLength / numRows)) {
        (*startColumn) = 0;
    }
    grabArraySection(displayArray, displayLength, inputArray, inputLength, numRows, *startColumn);
    (*startColumn)++;
}



void Multiplexer::displayBoolArray(bool* highArray, int arrayLen, int num_rows){
    int DISPLAY_CYCLES = 10; //Sets how long array is displayed for
    
    int num_columns = arrayLen / num_rows;
    while(DISPLAY_CYCLES--){
        // make array for lowRegister outputs
        bool* lowArray = (bool*)malloc(num_rows * sizeof(bool));
        memset(lowArray, 1, num_rows * sizeof(bool));
        int previous = 0;

        if (lowArray != NULL){
            for (int counter = 0; counter < num_rows; counter+= 1){
                _highRegister.setArray_toMemory(&highArray[counter * num_columns], num_columns);
                
                // Set the correct row pins to low
                for(int pos = 0; pos < num_rows; pos++){
                    if (counter == pos){ // this is the current row we are on (this row needs to turn on)
                        lowArray[pos] = 0;
                    }
                    else{ // turn all of the other rows off
                        lowArray[pos] = 1;
                    }
                }
                lowArray[previous] = 1;
                lowArray[counter] = 0;
                previous = counter;
                _lowRegister.setArray_toMemory(lowArray, num_rows);

                // Display the memory on the outputs
                _highRegister.pushMemory();
                _lowRegister.pushMemory();
                delay(CYCLE_TIME_ON); // leave the LED's on for a short time
            }
            
            // done with loop free array
            free(lowArray);
            lowArray = nullptr;
        }
    }

    //prevent dangling lights after completion
    _highRegister.clearMemory();
    _highRegister.pushMemory();
}

void printBoolArray(bool* array, int num_rows, int num_columns){
  for(int i = 0; i < num_rows*num_columns; i++){
    if (i%num_rows == 0){
      Serial.println("");
    }
    Serial.print(array[i]);
  }
  Serial.println("");
}

void Multiplexer::sendData(bool* highArray, int arrayLen, int num_rows, int action){

    // Move the data to the right
    if (action == 1){
        rightShiftArray(_displayArray, _displaySize, highArray, arrayLen, num_rows, &_startColumn);
    }

    else if (action == 2){
        leftShiftArray(_displayArray, _displaySize, highArray, arrayLen, num_rows, &_startColumn);
    }

    else if (action == 4) {
        int maxShift = (arrayLen / num_rows) - (_displaySize / num_rows) - 1;
        _startColumn = (arrayLen / num_rows) - (_displaySize / num_rows);
        // Shift right until the end
        for (int i = 0; i <= maxShift; i++) {
            sendData(highArray, arrayLen, num_rows, 1);
        }
        // Shift left back to the start
        for (int i = 0; i <= maxShift; i++) {
            sendData(highArray, arrayLen, num_rows, 2);
        }
    }
    else if (action == 5) {
        int maxShift = (arrayLen / num_rows) - (_displaySize / num_rows) - 1;
        _startColumn = 0;
        // Shift left back to the start
        for (int i = 0; i <= maxShift; i++) {
            sendData(highArray, arrayLen, num_rows, 2);
        }
        // Shift right until the end
        for (int i = 0; i <= maxShift; i++) {
            sendData(highArray, arrayLen, num_rows, 1);
        }
    }

    //Display 0 pos
    else{
        grabArraySection(_displayArray, _displaySize, highArray, arrayLen, num_rows, 0);
    }

    //display the array
    displayBoolArray(_displayArray, _displaySize, num_rows);
}