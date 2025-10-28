%{
    #include "y.tab.h"
    #include <string.h>
%}

%%

[0-9]+ { strcpy(yylval.str, yytext); return NUM; }
[a-zA-Z][a-zA-Z0-9]* { strcpy(yylval.str, yytext); return IDENTI; }
[ \t]+ { ; }
[\n] { return END; }
. { return yytext[0]; }

%%

int yywrap() {
    return 1;
}