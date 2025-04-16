%{
#include "parser1.tab.h"
%}

%%
"if"          { return IF; }
"else"        { return ELSE; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
"=="|"!="|"<="|">="|"<"|">" { return REL_OP; }
"="           { return '='; }  // Recognize assignment
"{"           { return OPEN_BRACE; }
"}"           { return CLOSE_BRACE; }
"("           { return OPEN_PAREN; }
")"           { return CLOSE_PAREN; }
";"           { return SEMICOLON; }
[ \t\n]       ;  // Ignore whitespace
.             { printf("Invalid character: %c\n", yytext[0]); exit(1); }
%%

int yywrap() {
    return 1;  // Indicating the end of input
}