#include <stdio.h>

/* count lines in input */
main()
{
  int c, nl;

  nl = 0;
  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++nl;
  /* why do i get a capital D if I only print "%d" with no characters after */
  printf("%d \n", nl);
}
