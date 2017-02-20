/*
 * This is an expansion on the forever loop
 * It illustrates the macro expansion and
 * multiline macro expansion.
 *
 * You can put the end-of-statement semicolon 
 * in or out of the macro.
 */

#define forever for (;;) { printf("c"); \
                           pintf("0");}; /* infinite loop */
#define max

int main()
{
  forever
}
