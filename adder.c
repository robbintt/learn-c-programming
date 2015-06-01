#include <stdio.h>

/*
 * A simple adder with a few interesting details.
 * / <--(note the space between * / means this line is still a comment.
 * This sequence ends a multiline comment -> */  

int main() {
    int i = 1;
    i = add_one(i);
    printf("Result: %d\n", i);
        return 0;
}

int add_one(int input) {
    // Must have the ++ before the variable name or else it adds after setting
    // result to input.
    int result = ++input;    
    printf("Result: %d\n", result);
    return result;
}
