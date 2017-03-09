/* strlen reworked to take advantage of pointer subtraction
 *
 * valid pointer operations:
 * assignment of pointers of the same type
 * adding or subtracting a pointer and an integer
 * subtracting or comparing two "pointers to members of the same array"
 * assigning or comparing to zero
 *
 * INVALID (aka illegal):
 * (everything else)
 * adding two pointers
 * multiply, divide, shift, mask two pointers
 * add a float or a double to a pointer 
 * assign a pointer of one type to a pointer of 
 *    another type without a cast. (except for void *)
 */

int strlen(char *s);

int main()
{
  printf("%i\n", strlen("Hello world!"));
}

int strlen(char *s)
{
  char *p = s;

  while (*p != '\0')
    p++;
  // pointer subtraction is valid
  return p - s;
}
