%{
    #include "y.tab.h"
    #include <string.h>
%}

%%

a[a]* {  strcpy(yylval.str, yytext);  return A; }
b[b]* { strcpy(yylval.str, yytext); return B; }
[\n] { return END; }
. { return yytext[0]; }

%%

int yywrap() { return 1; }