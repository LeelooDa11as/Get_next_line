#include "get_next_line.h"

void exampleFunction() {
    // Static variable retains its value between function calls
    static int count = 0;
    
    // Increment and print the static variable
    count++;
    printf("Static variable count: %d\n", count);
}
/*
int main() {
    // Call the function multiple times
    exampleFunction();
    exampleFunction();
    exampleFunction();
    
    return 0;
}*/
