#include <stdio.h>

/* 
 *
 * The bitwise assign is just a = a & a
 *
 * not really sure why it yields 5 once then yields 4 idempotently.
 * think about this some and explain it when you feel like it.
 *
 */

int main()
{
  int test = 10;
  int a = 5;
  printf("Value of a %d\n", a);
  
  
  for (int i=0; i<10; i++) {
    a &= a;
    printf("Value of a %d\n", a);
  }

  return 0;
}
