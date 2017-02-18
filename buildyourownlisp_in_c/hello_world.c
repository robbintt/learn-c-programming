/*
 * `puts` is a simpler `printf`
 * `printf` does string formatting and returns the number of characters printed
 * `puts` adds a newline on the string, and apparently returns EOF is it fails
 * you can also apparently puts a character or character array but never printf one? needs more detail/consideration.
 *
 */

#include <stdio.h>

int main(int argc, char** argv)
{
  puts("Hello, world!");
  return 0;
}
