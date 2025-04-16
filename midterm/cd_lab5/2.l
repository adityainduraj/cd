%{
#include <stdio.h>
#include <string.h>
int words = 0, chars = 0, blanks = 0, lines = 0;
%}

%%
\n              { lines++; chars++; }
[ \t]+          { blanks += strlen(yytext); chars += strlen(yytext); }
[a-zA-Z0-9]+    { words++; chars += strlen(yytext); }
.               { chars += strlen(yytext); }
%%

int main(void) {
    yylex();
    printf("Words: %d\nCharacters: %d\nBlanks: %d\nLines: %d\n", words, chars, blanks, lines);
    return 0;
}
int yywrap() {
    return 1;
}
