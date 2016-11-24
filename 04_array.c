#include <stdio.h>

/*
 *
 * Lets demonstrate [] operator syntactic sugar
 * e1[e2] means *(e1+e2)
 *
 */

int add_one(int input) {
  // Must have the ++ before the variable name or else it adds after setting
  // result to input.
  int result = input+1;    
  return result;
}

int main() {
  int len = 10;
  
  // choose one of the two following declarations
  // int *(array+len)
  int array[len];

  for(int i=0; i<len; i++) {
    int result = add_one(i);
    array[i] = result;
    printf("Value of i: %d\n", array[i]);
    printf("Memory Address: %p\n", &array[i]);
  }
  return 0;
}

