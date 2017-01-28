#include <stdio.h>

/* count lines in input */
main()
{
  int c, nl, blank, tab;

  nl = blank = tab = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n')
      ++nl;
    if (c == ' ')
      ++blank;
    if (c == '\t')
      ++tab;
  }
  /* why do i get a capital D if I only print "%d" with no characters after */
  printf("newlines: %d\n", nl);
  printf("blanks: %d\n", blank);
  printf("tabs: %d\n", tab);
}
