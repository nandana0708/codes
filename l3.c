#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    ARITHMETIC_OPERATOR,
    RELATIONAL_OPERATOR,
    LOGICAL_OPERATOR,
    SPECIAL_SYMBOL,
    KEYWORD,
    NUMERICAL_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER,
    COMMENT,
    PREPROCESSOR_DIRECTIVE,
    INVALID_TOKEN,
    END_OF_FILE
} TokenType;

// Token structure
typedef struct {
    int row;
    int column;
    TokenType type;
    char lexeme[100];
} Token;

// Function to check if a string is a keyword
int isKeyword(char *word) {
    char *keywords[] = {"int", "float", "char", "if", "else", "while", "for", "return"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // Keyword found
        }
    }
    return 0; // Not a keyword
}

// Function to get the next token
Token getNextToken(FILE *file) {
    Token token;
    char ch;
    int index = 0;

    // Initialize the token
    token.row = 1;
    token.column = 0;
    token.type = INVALID_TOKEN;
    strcpy(token.lexeme, "");

    // Read characters until a valid token is found
    while ((ch = fgetc(file)) != EOF) {
        // Update column count for non-space characters
        if (!isspace(ch)) {
            token.column++;
        }

        // Check for single line comment
        if (ch == '/' && (ch = fgetc(file)) == '/') {
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            token.row++;
            token.column = 0;
            continue;
        }

        // Check for multi-line comment
        if (ch == '/' && (ch = fgetc(file)) == '*') {

            while (1) {
                ch = fgetc(file);
                if (ch == '*' && (ch = fgetc(file)) == '/') {
                    token.type = COMMENT;
                    break;
                } else if (ch == '\n') {
                    token.row++;
                    token.column = 0;
                } else {
                    token.column++;
                }
            }

            continue;
        }

        // Check for preprocessor directive
        if (ch == '#') {
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            token.row++;
            token.column = 0;
            continue;
        }

        // Check for whitespace characters
        if (isspace(ch)) {
            if (ch == '\n') {
                token.row++;
                token.column = 0;
            }
            continue;
        }

        // Check for identifiers and keywords
        if (isalpha(ch) || ch == '_') {
            token.lexeme[index++] = ch;
            while (isalnum(ch = fgetc(file)) || ch == '_') {
                token.lexeme[index++] = ch;
            }
            token.lexeme[index] = '\0';
            token.column += index;

            if (isKeyword(token.lexeme)) {
                token.type = KEYWORD;
            } else {
                token.type = IDENTIFIER;
            }

            break;
        }

        // Check for numerical constants
        if (isdigit(ch)) {
            token.lexeme[index++] = ch;
            while (isdigit(ch = fgetc(file))) {
                token.lexeme[index++] = ch;
            }
            token.lexeme[index] = '\0';
            token.column += index;
            token.type = NUMERICAL_CONSTANT;
            break;
        }

        // Check for string literals
        if (ch == '"') {
            token.lexeme[index++] = ch;
            while ((ch = fgetc(file)) != '"') {
                token.lexeme[index++] = ch;
            }
            token.lexeme[index++] = '"';
            token.lexeme[index] = '\0';
            token.column += index;
            token.type = STRING_LITERAL;

            break;
        }

        // Check for special symbols
        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
                token.type = ARITHMETIC_OPERATOR;
                break;
            case '<':
            case '>':
            case '=':
            case '!':
                token.type = RELATIONAL_OPERATOR;
                break;
            case '&':
            case '|':
                token.type = LOGICAL_OPERATOR;
                break;
            case ';':
            case ',':
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
                token.type = SPECIAL_SYMBOL;
                break;
        }

        if (token.type != INVALID_TOKEN) {
            token.lexeme[index++] = ch;
            token.lexeme[index] = '\0';
            token.column++;
            break;
        }
    }

    if (ch == EOF) {
        token.type = END_OF_FILE;
    }

    return token;
}

// Function to print token information
void printToken(Token token) {
    printf("Row: %d, Column: %d, Type: %d, Lexeme: %s\n", token.row, token.column, token.type, token.lexeme);
}

int main() {
    FILE *inputFile;
    char inputFileName[100];
    Token token;

    // Get input file name
    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    // Open input file
    inputFile = fopen(inputFileName, "r");

    // Check if the file exists
    if (inputFile == NULL) {
        printf("Error: Unable to open the input file.\n");
        return 1;
    }

    // Process the input file and print tokens
    do {
        token = getNextToken(inputFile);
        if (token.type != COMMENT && token.type != PREPROCESSOR_DIRECTIVE && token.type != END_OF_FILE) {
            printToken(token);
        }
    } while (token.type != END_OF_FILE);

    // Close the file
    fclose(inputFile);

    return 0;
}

