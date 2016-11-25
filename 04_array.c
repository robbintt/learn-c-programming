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
  int array[len];

  for(int i=0; i<len; i++) {
    int result = add_one(i);
    // two options for how to access array:
    // array[i] = result;
    *(array + i) = result;
    printf("Value of i: %d\n", array[i]);
    printf("Memory Address: %p\n", &array[i]);
  }

  return 0;
}

