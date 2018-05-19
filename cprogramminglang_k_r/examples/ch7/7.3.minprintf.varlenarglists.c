#include <stdarg.h>

// not included in k&r p.156
#include <stdio.h>

/* minprintf: minimal printf with variable argument list */
/* printf returns the character count and is declared as int */
/* if you use an ellipsis, ..., then it means the NUMBER and TYPE of the arguments may vary. */
/* stdarg.h contains ... */
void minprintf(char *fmt, ...)
{
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival;
  double dval;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg in turn */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}

int main()
{
  minprintf("hello world!\n");
  // must include a \0 at the end of any string OR
  // give the number of characters e.g. %1s

  // be sure to use double quotes on the string, single quotes denote char
  minprintf("int: %d double: %f, str: %s\n", 5, 5.555555, "hello world!");
  return 0;
}
