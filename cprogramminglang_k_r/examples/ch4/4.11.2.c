/*
 * This is an expansion on the forever loop
 * It illustrates the macro expansion and
 * multiline macro expansion.
 *
 * You can put the end-of-statement semicolon 
 * in or out of the macro.
 */
#include <stdio.h>

#define forever for (;;) { printf("c"); \
                           printf("0");}; /* infinite loop */
// example of undef (uncomment result)
#undef forever

#define max(A, B) ((A) > (B) ? (A) : (B))

// note that the # prints the value of `expr`, the argument in the dprint() 'call'
// note that \ is replaced by \\ and " is replaced by \"
# define dprint(expr) printf(#expr " = %i\n", expr)
# define escprint(expr) printf(#expr)

//
// k&r p.91 says "The rules for nested uses of ## are arcane; further details may be found in Appendix A."
#define paste(front, back) front ## back

// the macro is undef'd above this declaration
int forever()
{
  printf("not forever\n");
  return 0;
}

int example_function()
{
  int x = 10;
  int y = 5;
  dprint(x/y);
  // make and print a string
  char madstring[] = "no madness here: \\ and \" work";
  printf("madstring = '%s'\n", madstring);
  // prints the raw newline...
  escprint("madness \\ and \"\n");
  printf("\n");
  // prints the string 'madstring', does not do variable substitution
  escprint(madstring);
  // prints the string with backslash type esc character substitution
  escprint(madstring\n);
  // prints 5 escaped backslashes (normal substitution, another illustration)
  escprint(madstring\\\\\\\\\\);
  printf("\n");
  return 0;
}


int main()
{
  int p = 1, q = 2, r = 3, s = 4;
  // max() result is 7 = (r+s)
  printf("%i\n", max(p+q, r+s)); // note the semicolon is in the macro.

  // note that a macro cannot have a semicolon if it isn't the end of its substitution.
  // putting a semicolon at the end of the macro is bad for composability but it does work when syntactically correct.
  // forever // the macro has no () and contains the ; for fun (because it ends the line)
  forever(); // this is the function call, it does not run forever
  example_function();
  // yields the static string 'name1'
  // char pasted[] = paste(name, 1);  // doesn't work
  char name1[] = "a char array";
  // we can compose the token name1 and get "a char array" out
  printf("%s\n", paste(name, 1));
}



