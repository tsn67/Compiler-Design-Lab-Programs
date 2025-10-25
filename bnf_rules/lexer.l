%{
    #include "y.tab.h"   
    #include <stdio.h>
%}

%%

main { return MAIN; }
float|int|void { return TYPE; }
if { return IF; }
else { return ELSE; }
while { return WHILE; }
>=|<=|==|>|<  { return RELOP; }
[0-9]+ { return DIGIT; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTI; }
[ \n] ;
. { return yytext[0]; }

%%

int yywrap() {
    return 1;
}