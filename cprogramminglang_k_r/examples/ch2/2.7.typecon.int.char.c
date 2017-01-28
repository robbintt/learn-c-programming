#include <stdio.h>

#define STEP 1
#define ROT 257 /* one overlap */


int main()
{
  printf("Step size STEP: %i\n", STEP);
  /* lets cycle through some conversions and examine the nature of the overflow */
  for (int i=0; i<ROT; i=i+STEP) {
    int j=i;
    char c;
    /* signed int! */
    /* note that the value is truncated to a modulus */

    printf("5x(int->char,char->int): ");
    for (int t=0; t<10; ++t)
      printf("%c %i ", c=j, j=c);
    printf("\n");
  }
}
