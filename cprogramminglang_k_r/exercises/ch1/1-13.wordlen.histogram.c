#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
  int c, state;
  int curlen=0;
  int strhist[100] = {0};
  state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        /* increment the array associated with this word length, curlen */
        if (0 < curlen && curlen < 100)
          strhist[curlen] += 1;
        else
          ; /* manage edge case */
        curlen = 0;
      }
    }
    else {
      state = IN;
      curlen += 1;
    }
  }
  for (int i=0; i<100; i++)
    printf("%4d %4d\n", i, strhist[i]);
}
