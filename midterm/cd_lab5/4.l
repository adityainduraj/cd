%{
#include <stdio.h>

int scanf_count = 0, printf_count = 0;
%}

%%
scanf { printf("READ"); scanf_count++; }   // Replace 'scanf' with 'READ' and count occurrences
printf { printf("WRITE"); printf_count++; } // Replace 'printf' with 'WRITE' and count occurrences
. { putchar(yytext[0]); }                   // Print everything else as is
%%

int main() {
    printf("Modified Output:\n\n");
    yylex();
    printf("\n\nTotal 'scanf' replaced: %d\n", scanf_count);
    printf("Total 'printf' replaced: %d\n", printf_count);
    return 0;
}

int yywrap() {
    return 1;
}
