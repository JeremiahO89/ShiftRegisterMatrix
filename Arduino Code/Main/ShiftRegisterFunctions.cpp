#include "Arduino.h"
#include "ShiftRegister.h"

# define DEBOUNCE 1   //1 millisecond 

void ShiftRegister::setArray_toMemory(int *array, int array_size) {
  /*
  Inputs: int[] : array , int:array_size
  Outputs: None
  Process: Set the shift register memory based on the values in the array
  */

  // prevent dangling values at the end of the matrix
  if(array_size != _num_outputs){
    clearMemory(); // clear current memory
  }

  // set memory based on array
  for (int index = 0; index < array_size; index ++){
    if (array[index)]{
      highState();
    }
    else{
      lowState();
    }
    pushState();
  }
}


