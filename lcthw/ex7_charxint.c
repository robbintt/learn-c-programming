#include <stdio.h>

int main(int argc, char *argv[])
{
  int distance = 100;
  char initial = 'A';
  char first_name[] = "Zed";

  printf("You are %d miles away.\n", distance);
  printf("I have an initial %c.\n", initial);
  printf("My whole name is %s %c.\n", 
          first_name, initial);
  //printf("This is only a %e portion of the universe.\n", 
  //       part_of_universe);

  // this makes no sense, just a demo of something weird
  char nul_byte = '\0';
  int care_percentage = 100 * nul_byte;
  printf("Which means you should care %d%%.\n", care_percentage);

  // in the ascii decimal set, 'A' == 65 and this is what we see.
  printf("Lets view a char as an int: %d -- what did we get?\n", initial);

  // the decimal output is 6500
  // lowercase 'd' == 100 in asci decimal and that is output.
  // 6500 % 256 = 100 so the ascii table displays modulus 256 of the integer
  int charxint = initial * 100;
  printf("What number is charint? %d\nWhat letter is charint? %c\n", charxint, charxint);
  
  // char charxint2[] = initial * 100;
  // printf("How about as a character array? %s\n", charxint2);
  
  return 0;
}
