#include "Multiplexer.h"
#include "ShiftRegister.h"

#include <Arduino.h>

# define CYCLE_TIME_ON 2 //1.5 millisecond

Multiplexer::Multiplexer(ShiftRegister& highRegister, ShiftRegister& lowRegister): _highRegister(highRegister), _lowRegister(lowRegister){
}

void leftShiftArray(bool* highArray, int arrayLen, int num_rows){
    int numColumns = arrayLen/num_rows;
    for(int pos = 0; pos<num_rows; pos++){
        //shift each row 1 bit
        memmove(&highArray[pos*numColumns], &highArray[numColumns*pos+1], (numColumns-1) * sizeof(bool));
        //set last element in row to zero
        highArray[(pos + 1) * numColumns - 1] = 0;
    }
}
void rightShiftArray(bool* highArray, int arrayLen, int num_rows) {
   int numColumns = arrayLen/num_rows;
   for(int pos = 0; pos<num_rows; pos++){
        //shift each row 1 bit
        memmove(&highArray[numColumns*pos+1], &highArray[numColumns*pos], (numColumns-1) * sizeof(bool));
        //set first element in row to zero
        highArray[numColumns* pos] = 0;
    }
}

void Multiplexer::displayBoolArray(bool* highArray, int arrayLen, int num_rows, int num_columns){
    int DISPLAY_CYCLES = 10; //Sets how long it stays on
    while(DISPLAY_CYCLES--){
        // make array for lowRegister outputs
        bool* lowArray = (bool*)malloc(num_rows * sizeof(bool));
        memset(lowArray, 1, num_rows * sizeof(bool));
        int previous = 0;

        if (lowArray != NULL){
            for (int counter = 0; counter < num_rows; counter+= 1){
                _highRegister.setArray_toMemory(&highArray[counter * num_columns], num_columns);
                
                // Set the correct row pins low
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


void Multiplexer::sendData(bool* highArray, int arrayLen, int action, int num_rows, int num_columns){
    // Move the data to the right
    if (action == 1){
        rightShiftArray(highArray, arrayLen, num_rows);
    }
    else if(action == 2){
        leftShiftArray(highArray, arrayLen, num_rows);
    }
    else if(action == 3){
        int counter = _highRegister._num_outputs;
        
        while (counter--){
            sendData(highArray, arrayLen, 1, num_rows , num_columns);
              for(int i = 0; i < num_rows*num_columns; i++){
                    if (i%num_rows == 0){
                    Serial.println("");
                    }
                    Serial.print(highArray[i]);
                }
                Serial.println("");
        }
        while (counter < (_highRegister._num_outputs - 1)){
            sendData(highArray, arrayLen, 2, num_rows , num_columns);
            counter ++;
        }
    }
    else if(action == 4){
        int counter = _highRegister._num_outputs;
        
        while (counter--){
            sendData(highArray, arrayLen, 2, num_rows , num_columns);
        }
        while (counter < (_highRegister._num_outputs - 1)){
            sendData(highArray, arrayLen, 1, num_rows , num_columns);
            counter ++;
        }
    }
    //display the array
    displayBoolArray(highArray, arrayLen, num_rows, num_columns);
}