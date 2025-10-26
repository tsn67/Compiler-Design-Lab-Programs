%{
    #include <stdio.h>
    
    extern FILE* yyin;
%}

%left '+' '-'
%left '*' '/'
%token MAIN IF TYPE ELSE WHILE RELOP IDENTI DIGIT

%%
S: E { printf("Successful!\n"); return 1; }
E: TYPE MAIN '(' ')' BLOCK
;
BLOCK: '{' STATLIST '}'
;
STATLIST: STAT STATLIST
|
;
STAT: DECL
| ASSI
| IFSTAT
| WHILSTAT
;
DECL: TYPE T ';'
;
T: T ',' IDENTI 
| IDENTI
;
ASSI: IDENTI '=' EXPR ';'
;
EXPR: EXPR '+' M
| EXPR '-' M
| M
;
M: M '*' F
| M '/' F
| F
;
F: '(' EXPR ')'
| IDENTI
| DIGIT
;
IFSTAT: IF '('  C ')' BLOCK TAIL
TAIL: ELSE BLOCK
|
;
C: EXPR
| C RELOP EXPR
;
WHILSTAT: WHILE '(' C ')' BLOCK
;

%%

void yyerror(char* s) {
    printf("Syntax Error!\n");
    yyrestart(stdin);
}

int main(int argc, char* rcvg[]) {
    printf("input filie: %s\n", rcvg[1]);
    FILE* f1 = fopen(rcvg[1], "r");
    yyin = f1;

    yyparse();
}