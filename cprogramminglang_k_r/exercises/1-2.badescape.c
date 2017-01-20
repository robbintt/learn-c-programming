#include <stdio.h>

main()

{
  /* nonexistent escapes generate a warning and are ignored */
  printf("\c\j\7\@");
}
