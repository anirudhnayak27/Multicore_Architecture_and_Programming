#include <stdio.h>

// Define global variables
int SIZE = 9;
int MINIGRIDSIZE = 3;
int thread_count = 4;

// Function prototypes
void someSudokuFunction();

int main(int argc, char *argv[]) {

    SIZE = 16;
    // Print the value of SIZE in main.c
    printf("SIZE in main.c: %d\n", SIZE);

    // Call the function defined in sudoku.c
    someSudokuFunction();

    return 0;
}
