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
// example of undef (uncomment result)
#undef forever

#define max(A, B) ((A) > (B) ? (A) : (B))

// the macro is undef'd above this declaration
int forever()
{
  printf("not forever\n");
  return 0;
}

int main()
{
  int p = 1, q = 2, r = 3, s = 4;
  // max() result is 7 = (r+s)
  printf("%i\n", max(p+q, r+s)); // note the semicolon is in the macro.

  // note that a macro cannot have a semicolon if it isn't the end of its substitution.
  // putting a semicolon at the end of the macro is bad for composability but it does work when syntactically correct.
  // forever // the macro has no () and contains the ; for fun (because it ends the line)
  forever();
}



