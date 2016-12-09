#include <stdio.h>

int main(int argc, char *argv[])
{
  int i=0;

  // this for is absurd to read, as bad as PHP
  // consider a better whitespace construction
  // for the if / else if / else syntax
  //
  // question: can i have unlimited else ifs?
  //
  // note: the else if statement is PROBABLY a compound
  // statement of 'if' and 'else' that really is just a
  // nested else.
  // this IMPLIES that you can have unlimited `else if`s
  //
  if (argc == 1) {
    
    printf("You only have one argument.\n");

  } else if (argc > 1 && argc < 4) {

    printf("Here's your arguments:\n");

    for (i=0; i<argc; i++) {
      printf("%s ", argv[i]);
    }
    printf("\n");
    
  } else {

    printf("You have too many arguments.\n");

  }

  // ok but lets see argc and argv
  printf("argc: %d\n", argc);
  // how do i dereference this kind of string thingy
  printf("argv: %s\n", *argv);
  printf("argv: %s\n", argv[1]);
  printf("argv: %s\n", argv[2]);
  printf("argv: %s\n", argv[3]);


  return 0;
}
