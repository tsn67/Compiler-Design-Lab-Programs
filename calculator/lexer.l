%{
    #include "y.tab.h"   
    #include <stdlib.h>
%}

%%

[0-9]+ { yylval.val = atoi(yytext); return NUM; }
[\n] { return END; }
[ ] ;
. { return yytext[0]; }

%%

int yywrap() { return 1; }