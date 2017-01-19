#include <stdio.h>

#define LOWER 0 /* lower limit of table */
#define UPPER 300 /* upper limit of table */
#define STEP 20 /* step size */

float fahr_to_c(int fahr);

/* print Fahrenheit-Celsius table */
main()
{
  int fahr;

  for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
    printf("%3d %6.1f\n", fahr, fahr_to_c(fahr)); 
}

float fahr_to_c(int fahr)
{
  return (5.0/9.0)*(fahr-32);
}
