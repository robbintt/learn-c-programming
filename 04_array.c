#include <stdio.h>

/*
 * There are some interesting questions here. 
 *
 * Why is the memory address in the for loop unchanged?
 *
 *
 *
 */

int main() {
  int i;
  int array[5];
  int *array_ptr = array;
  printf("Value of i: %d\n", array[0]);
  printf("Memory Address: %p\n", array_ptr);
  /*
  for(i=0; i<10; i++) {
    int result = add_one(i);
    int *result_pointer = &result;
    printf("Value of i: %d\n", result);
    printf("Memory Address: %p\n", result_pointer);
  }
  */
  return 0;
}

int add_one(int input) {
  // Must have the ++ before the variable name or else it adds after setting
  // result to input.
  int result = input+1;    
  return result;
}
