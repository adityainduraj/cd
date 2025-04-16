%{
    #include <stdio.h>
    #include <stdlib.h>

    // Function prototypes
    void yyerror(const char *s);
    int yylex();
%}

%define parse.error verbose
  // Enable detailed error messages

%token IF ELSE IDENTIFIER REL_OP OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN SEMICOLON

%%
decision_statement: IF OPEN_PAREN condition CLOSE_PAREN OPEN_BRACE statement_list CLOSE_BRACE
                   | IF OPEN_PAREN condition CLOSE_PAREN OPEN_BRACE statement_list CLOSE_BRACE ELSE OPEN_BRACE statement_list CLOSE_BRACE
                   {
                       printf("Valid decision-making statement.\n");
                   }
                   ;

condition: IDENTIFIER REL_OP IDENTIFIER
          ;

statement_list: statement SEMICOLON
              | statement SEMICOLON statement_list
              ;

statement: IDENTIFIER '=' IDENTIFIER  // Include assignment handling
          ;
%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

int main() {
    printf("Enter a decision-making statement:\n");
    yyparse();
    return 0;
}