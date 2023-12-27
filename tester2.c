#include <stdio.h>


// This is a global variable
int globalVariable = 10;

void myFunction() {
    // Accessing the global variable from within a function
    printf("Global variable value: %d\n", globalVariable);
}

int main() {
    // Accessing the global variable from the main function
    printf("Global variable value: %d\n", globalVariable);

    // Modifying the global variable
    globalVariable = 20;

    // Calling a function that uses the global variable
    myFunction();

    return 0;
}
