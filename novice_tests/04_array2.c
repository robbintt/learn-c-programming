#include <stdio.h>

/*
 *
 * Lets demonstrate populating an array with curly braces { .. }
 *
 */

int main() {

  int len = 10;
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for(int i=0; i<len; i++) {

    printf("Array location: %p\n", array);
    printf("Array dereference: %d\n", *array);
    printf("Value of i: %d\n", array[i]);
    printf("Memory Address: %p\n", &array[i]);
    printf("--- --- --- --- --- --- ---\n");
  }

  return 0;
}

