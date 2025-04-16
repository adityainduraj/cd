%{
#include "parser.tab.h"
%}

%%
"int"       { return INT; }
"char"      { return CHAR; }
"float"     { return FLOAT; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
","         { return COMMA; }
";"         { return SEMICOLON; }
[ \t\n]     ;  // Ignore whitespace
.           { printf("Invalid character: %c\n", yytext[0]); exit(1); }
%%

int yywrap(){
    return 1;
}