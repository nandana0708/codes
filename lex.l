%option noyywrap

DIGIT [0-9]
LETTER [a-zA-Z]

%{
#include "y.tab.h"
%}

%%

int     { return INT; }
float   { return FLOAT; }
char    { return CHAR; }
double  { return DOUBLE; }

{LETTER}({LETTER}|{DIGIT})*  { return IDENTIFIER; }
{DIGIT}+                    { return INTEGER; }

=       { return EQUAL; }
;       { return SEMICOLON; }

[ \t\n]                     ; // Ignore whitespace
.                           { return *yytext; }

%%


