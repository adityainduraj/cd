%{
#include <stdio.h>
int posInt = 0, negInt = 0, posFloat = 0, negFloat = 0;
%}

%%
[+]?([0-9]+\.[0-9]+)    { posFloat++; }
-[0-9]+\.[0-9]+         { negFloat++; }

[+]?([0-9]+)           { posInt++; }
-[0-9]+                { negInt++; }
[ \t\n]+               { /* ignore whitespace */ }
.                      { /* ignore any other characters */ }
%%

int main(void) {
    yylex();
    printf("Positive Integers: %d\n", posInt);
    printf("Negative Integers: %d\n", negInt);
    printf("Positive Floats: %d\n", posFloat);
    printf("Negative Floats: %d\n", negFloat);
    return 0;
}
int yywrap() {
    return 1;
}
