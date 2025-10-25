%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <string.h>
%}

%%

[0-9]+ { yylval.num = atoi(yytext); return DIGIT; }
[a-zA-Z][0-9a-zA-Z]* { strcpy(yylval.str, yytext); return IDENT; }
[\n] { return END; }
. { return yytext[0]; }

%%

int yywrap() {
    return 1;
}