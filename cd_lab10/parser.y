%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototypes
void yyerror(const char *s);
int yylex();
%}

%token INT CHAR FLOAT IDENTIFIER COMMA SEMICOLON

%%
declaration: type identifier_list SEMICOLON
            {
                printf("Valid declaration statement.\n");
            }
            ;

type: INT
    | CHAR
    | FLOAT
    ;

identifier_list: IDENTIFIER
               | IDENTIFIER COMMA identifier_list
               ;

%%

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

// Entry point of the program
int main() {
    printf("Enter a declaration statement:\n");
    yyparse();
    return 0;
}
