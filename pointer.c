#include <stdio.h>

/*
 * A simple adder with a few interesting details.
 * / <--(note the space between * / means this line is still a comment.
 * This sequence ends a multiline comment -> */  

int main() {
    int i;
    for(i=0; i<10; i++) {
    printf("Result: %d\n",  add_one(i));
    }
    return 0;
}

int add_one(int input) {
    // Must have the ++ before the variable name or else it adds after setting
    // result to input.
    int result = input+1;    
    printf("Inside add_one: %d\n", result);
    return result;
}
