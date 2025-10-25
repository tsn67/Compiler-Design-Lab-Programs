%{
    #include "y.tab.h"
    #include <stdio.h>
%}

%%

[0-9]+ { strcpy(yylval.str, yytext); return NUM; }
[a-z]+ { strcpy(yylval.str, yytext); return VAR; }
[\n] { return END; }
.  { return yytext[0]; }

%%

int yywrap() {
    return 1;
}