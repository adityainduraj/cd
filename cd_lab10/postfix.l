%{
#include "postfix.tab.h"
%}

%%
[0-9]+(\.[0-9]+)?  { yylval.val = atof(yytext); return NUM; }
[+\-*/^]           { return *yytext; }
"n"                { return 'n'; }
[\n]               { return '\n'; }
[ \t]              ;  // Ignore spaces and tabs
.                  { printf("Invalid character: %c\n", yytext[0]); exit(1); }
%%

int yywrap() {
    return 1;  // Indicating the end of input
}