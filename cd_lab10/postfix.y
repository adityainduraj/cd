%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototypes
void yyerror(const char *s);
int yylex();
%}

%union {
    double val;  // Use double for numbers and results
}

%token <val> NUM
%left '+' '-'
%left '*' '/'
%right '^'

%type <val> exp  // "exp" propagates values
%type line       // "line" does not propagate values

%%
input: input line
     | /* Empty input (epsilon) */
     ;

line: '\n'
    | exp '\n' { printf("Result: %f\n", $1); }  // Print the result of the expression
    ;

exp: NUM                   { $$ = $1; }
   | exp exp '+'           { $$ = $1 + $2; }
   | exp exp '-'           { $$ = $1 - $2; }
   | exp exp '*'           { $$ = $1 * $2; }
   | exp exp '/'           { 
                                 if ($2 == 0) {
                                     yyerror("Division by zero");
                                     YYERROR;
                                 }
                                 $$ = $1 / $2; 
                             }
   | exp exp '^'           { $$ = pow($1, $2); }
   | exp 'n'               { $$ = -$1; }
   ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter postfix expressions (e.g., 3 4 +):\n");
    yyparse();
    return 0;
}


