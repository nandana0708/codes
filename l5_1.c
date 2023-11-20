#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void error();
void match(char expectedToken);
void S();
void T();

// Input string
char input[100];
// Current position in the input string
int currentPosition;

int main() {
    printf("Enter the input string: ");
    scanf("%s", input);

    // Start parsing from the beginning of the input
    currentPosition = 0;
    S();

    // Check if the entire input is parsed
    if (input[currentPosition] == '\0') {
        printf("Parsing successful!\n");
    } else {
        printf("Parsing failed!\n");
    }

    return 0;
}

// Function to print an error message and exit
void error() {
    printf("Error: Parsing failed at position %d\n", currentPosition);
    exit(1);
}

// Function to match the current token
void match(char expectedToken) {
    if (input[currentPosition] == expectedToken) {
        currentPosition++;
    } else {
        error();
    }
}

// Grammar rules
void S() {
    if (input[currentPosition] == 'a') {
        match('a');
    } else if (input[currentPosition] == '>') {
        match('>');
    } else if (input[currentPosition] == '(') {
        match('(');
        T();
        match(')');
    } else {
        error();
    }
}

void T() {
    S();
    if (input[currentPosition] == ',') {
        match(',');
        T();
    }
}

