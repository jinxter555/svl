%{
#include <stdio.h>
#include "parser.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*   { yylval.str = strdup(yytext); return ID; }
[0-9]+    { yylval.num = atoi(yytext); return NUM; }
","       { return COMMA; }
"iadd"                { return IADD; }
"mov"                 { return MOV; }
[ \t\n]               ; // Ignore whitespace
.                     { return yytext[0]; } // Any other character
%%

int yywrap() { return 1; }


