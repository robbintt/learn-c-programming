#include <stdio.h>

int main()
{
  int i2 = 5000;
  char c2 = 'a';

  /* this is stable because char is not "higher than" c */
  printf("char->int->char %i %c %i %c\n", c2, i2=c2, c2=i2, i2=c2);

}
