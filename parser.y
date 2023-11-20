%{
#include <stdio.h>
#include <stdlib.h>
%}

%token INT FLOAT CHAR DOUBLE IDENTIFIER INTEGER EQUAL SEMICOLON

void yyerror(const char *s);

%%

input: /* empty */
     | input line
     ;

line: '\n'
    | declaration '\n' { printf("Valid declaration\n"); }
    ;

declaration: type IDENTIFIER SEMICOLON
           | type IDENTIFIER EQUAL value SEMICOLON { printf("Valid declaration with initializer\n"); }
           ;

type: INT | FLOAT | CHAR | DOUBLE;

value: INTEGER | FLOAT;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at token '%s': %s\n", yytext, s);
}

int main() {
    yyparse();
    return 0;
}
