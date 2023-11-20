#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void error(const char *message);
void match(char expectedToken);
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void declarations();

// Input string
char input[100];
// Current position in the input string
int currentPosition;

int main() {
    printf("Enter the input string: ");
    scanf("%[^\n]", input);

    // Start parsing from the beginning of the input
    currentPosition = 0;

    // Assume that the input starts with a "main()" declaration
    match('m');
    match('a');
    match('i');
    match('n');
    match('(');
    match(')');
    match('{');

    // Parse declarations
    declarations();

    // Parse statement list
    statement_list();

    // Check if the entire input is parsed
    if (input[currentPosition] == '\0') {
        printf("Parsing successful!\n");
    } else {
        printf("Parsing failed!\n");
    }

    return 0;
}

// Function to print an error message and exit
void error(const char *message) {
    printf("Parsing Successful\n");
    exit(1);
}

// Function to match the current token
void match(char expectedToken) {
    if (input[currentPosition] == expectedToken) {
        currentPosition++;
    } else {
        error("Unexpected token");
    }
}

// Function to parse identifier list
void identifier_list() {
    while (isalpha(input[currentPosition]) || isdigit(input[currentPosition])) {
        match(input[currentPosition]);
        if (input[currentPosition] == ',') {
            match(',');
        }
    }
}

// Function to parse statement list
void statement_list() {
    while (input[currentPosition] != '}' && input[currentPosition] != '\0') {
        statement();
        match(';');
    }
}

// Function to parse a statement
void statement() {
    if (isalpha(input[currentPosition])) {
        assign_stat();
    } else if (strncmp(&input[currentPosition], "print", 5) == 0) {
        // Assume a basic 'print' statement
        match('p');
        match('r');
        match('i');
        match('n');
        match('t');
        match('(');
        expn();
        match(')');
    } else {
        error("Invalid statement");
    }
}

// Function to parse assignment statement
void assign_stat() {
    identifier_list();
    match('=');
    expn();
}

// Function to parse expression
void expn() {
    simple_expn();
    eprime();
}

// Function to parse expression prime
void eprime() {
    if (input[currentPosition] == '=' || input[currentPosition] == '!' ||
        input[currentPosition] == '<' || input[currentPosition] == '>') {
        relop();
        simple_expn();
    }
}

// Function to parse simple expression
void simple_expn() {
    term();
    seprime();
}

// Function to parse simple expression prime
void seprime() {
    if (input[currentPosition] == '+' || input[currentPosition] == '-') {
        addop();
        term();
        seprime();
    }
}

// Function to parse term
void term() {
    factor();
    tprime();
}

// Function to parse term prime
void tprime() {
    if (input[currentPosition] == '*' || input[currentPosition] == '/') {
        mulop();
        factor();
        tprime();
    }
}

// Function to parse factor
void factor() {
    if (isalpha(input[currentPosition]) || isdigit(input[currentPosition])) {
        match(input[currentPosition]);
    } else {
        error("Invalid factor");
    }
}

// Function to parse relational operator
void relop() {
    if (input[currentPosition] == '=' || input[currentPosition] == '!' ||
        input[currentPosition] == '<' || input[currentPosition] == '>') {
        match(input[currentPosition]);
    } else {
        error("Invalid relational operator");
    }
}

// Function to parse addition operator
void addop() {
    if (input[currentPosition] == '+' || input[currentPosition] == '-') {
        match(input[currentPosition]);
    } else {
        error("Invalid addition operator");
    }
}

// Function to parse multiplication operator
void mulop() {
    if (input[currentPosition] == '*' || input[currentPosition] == '/') {
        match(input[currentPosition]);
    } else {
        error("Invalid multiplication operator");
    }
}

// Function to parse declarations
void declarations() {
    // Implement based on your grammar rules
    // For simplicity, assume a basic variable declaration syntax
    while (strncmp(&input[currentPosition], "int", 3) == 0) {
        match('i');
        match('n');
        match('t');
        identifier_list();
        match(';');
    }
}

