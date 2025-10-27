%{
    #include "y.tab.h"
    #include <string.h>
%}

/*
qn: WW^r, W = (a|b)*
eg. e, aa, abba, aaaaa, bb, bbaabb, ...
*/

%%

[ab]* { strcpy(yylval.str, yytext); return ABWORD; }
[\n] { return END; }
. { return yytext[0]; }

%%

int yywrap() { return 1; }