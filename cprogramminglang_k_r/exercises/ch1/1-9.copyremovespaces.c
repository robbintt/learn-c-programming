#include <stdio.h>

/* use the in/out idiom from the next example for convenience
 *
 * */


#define IN 0
#define OUT 1

int main()
{

  int c, state;

  state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (state == OUT) {
        putchar(c);
        state = IN;
      }
    } 
    else {
      state = OUT;
      putchar(c);
    }
  }
}
