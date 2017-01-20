#include <stdio.h>


/* The C Programming Language *
 * Page 17
 * Exercise 1-6
 * Verify the expression getchar() != EOF is 0 or 1
 * */
int main()
{
  int c;
  /* this assigns 0 or 1 to c instead of the character, oops! */
  c = (getchar() != EOF);
  /* printf("%c\n", c); */
  printf("%d\n", c); /* need to adjust this to print an integer */
}
