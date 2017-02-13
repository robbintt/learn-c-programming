#include <stdio.h>

/*
 * A simple adder with a few interesting details.
 * / <--(note the space between * / means this line is still a comment.
 * This sequence ends a multiline comment -> */  

// apparently in gcc99 add_one needs to be defined before it is used
// originally add_one() was defined after main()
// "warning: implicit declaration of function 'add_one' is invalid in C99"
int add_one(int input) {
  // Must have the ++ before the variable name or else it adds after setting
  // result to input.
  int result = ++input;    
  printf("(inside add_one) Result: %d\n", result);
  return result;
}

int main() {
  int i = 1;
  i = add_one(i);
  printf("(inside main) Result: %d\n", i);
    return 0;
}
