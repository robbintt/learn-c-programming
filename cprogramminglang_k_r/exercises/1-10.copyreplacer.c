#include <stdio.h>

/* use the in/out idiom from the next example for convenience
 *
 * to get this behavior, set your delete key to ^H in your terminal keys (tested in macos iterm2)
 * */

int main()
{

  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      putchar('\\');
      putchar('t');
    } 
    else if (c == '\\') {
      putchar('\\');
      putchar('\\');
    } 
    else if (c == '\b') {
      putchar('\\');
      putchar('b');
    } 
    else {
      putchar(c);
    }
  }
}
