/*
 * This is an expansion on the forever loop
 * It illustrates the macro expansion and
 * multiline macro expansion.
 *
 * You can put the end-of-statement semicolon 
 * in or out of the macro.
 */
#include <stdio.h>

#define forever for (;;) { printf("c"); \
                           printf("0");}; /* infinite loop */

#define max(A, B) ((A) > (B) ? (A) : (B))

int main()
{
  int p = 1, q = 2, r = 3, s = 4;
  printf("%i\n", max(p+q, r+s));
  // forever  // note the semicolon is in the macro, too.
}
