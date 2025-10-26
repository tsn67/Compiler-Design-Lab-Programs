%{
    #include <stdio.h>   
%}

%union {
    int val;
}

%token END
%token<val>  NUM
%type<val> E T F

%left '+' '-'
%left '/' '*'

%%

S: E END { printf("%d\n", $1); return 1; }
;
E: E '+' T { $$ = $1 + $3; }
| E '-' T  { $$ = $1 - $3; }
| T { $$ = $1; }
;
T: T '*' F { $$ = $1 * $3; }
| T '/' F { $$ = $1 / $3; }
| F { $$ = $1; }
;
F: '(' E ')' { $$ = $2; }
| NUM { $$ = $1; }
;

%%

void yyerror(char* s) {
    printf("Syntax Error!\n");
    yyrestart(stdin);
}

int main() {
    while(1) {
        printf("Enter expression: ");
        yyparse();
    }
}