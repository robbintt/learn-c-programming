/* 
 * note that i needed to substitute the 'getline' function name for
 * 'getaline' because of a function in stdio.h which conflicted 
 *
 * p.33 says this program is inferior to its predecessor because 
 * the extern and lack of variables as function arguments make the 
 * code challenging to read. Also, the functions lose their 
 * generality, becoming useful only in-context.
 *
 * */
#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int max;
char line[MAXLINE];
char longest[MAXLINE];

int getaline(void);
void copy(void);


/* print longest input line */
main()
{
  int len; /* current line length */
  extern int max; /* maximum line length seen so far */
  extern char longest[]; /* longest line saved here */

  max = 0;
  while ((len = getaline()) > 0)
    if (len > max) {
      max = len;
      copy();
    }
  if (max > 0) /* there was a line */
    printf("%s", longest);
  return 0;
}

/* getaline: read a line into s, return length */
int getaline(void)
{
  int c, i;
  extern char line[];

  for (i = 0; i < MAXLINE - 1 
      && (c=getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;

  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(void)
{
  int i;
  extern char line[], longest[];

  i = 0;
  while ((longest[i] = line[i]) != '\0')
    ++i;
}
