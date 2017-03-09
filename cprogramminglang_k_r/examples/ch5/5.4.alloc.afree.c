/* implement alloc and afree, a memory stack (a last-in, first-out list)
 * the standard library has malloc and free but they are not LIFO.
 * See section 8.7 for more on malloc and free */

/* k&r doesn't use these functions, consider making a toy use case */

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
  // note that this is ((pointer+int) - pointer) which is one of
  // very few valid operations on pointers
  // allocp is initialized as a pointer to the first element of allocbuf
  // allocbuf is also a pointer to the first element of itself
  // allocbuf+allocsize yields the last position of allocbuf in pointer format
  // this allows allocp to be subtracted; this gives remaining storage
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
    allocp += n;
    return allocp - n; /* old p*/
  } else // not enough room
    return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}
