#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */
main()
{
  float fahr, celsius;
  int lower, upper, step;
  
  lower = 0;
  upper = 100;
  step = 1;

  celsius = lower;
  printf(" *C     *F\n");
  while (celsius <= upper) {
    fahr = (celsius * (9.0/5.0)) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
