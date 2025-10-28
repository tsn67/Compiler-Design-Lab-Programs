%{
    #include <stdio.h>
    #include <string.h>

    extern FILE* yyin; 

    int t = 0;

    int print_3_code(char op, char* arg1, char* arg2) {
        printf("t%d %c %s %s\n", t, op, arg1, arg2);
        t++;
        return t - 1;
    }

    void get_res(char* res, int d) {
        sprintf(res, "t%d", d);
    }

%}

%union {
    char str[100];
}

%token END
%token<str> IDENTI NUM
%type<str> T F EXPR ASSIGN

%%

E: E ASSIGN
| E M
| ASSIGN
| M
;
ASSIGN: IDENTI '=' EXPR ';' END  { printf("%s = %s\n", $1, $3); }
;
M: EXPR ';' END
;
EXPR: EXPR '+' T { get_res($$, print_3_code('+', $1, $3)); }
| EXPR '-' T { get_res($$, print_3_code('-', $1, $3)); }
| T { strcpy($$, $1); }
;
T: T '*' F { get_res($$, print_3_code('*', $1, $3)); }
| T '/' F { get_res($$, print_3_code('/', $1, $3)); }
| F { strcpy($$, $1); }
;
F: '(' EXPR ')' { strcpy($$, $2); }
| IDENTI { strcpy($$, $1); }
| NUM { strcpy($$, $1); }
;



%%

void yyerror(char* s) {
    printf("Syntax Error!\n");
    yyrestart(stdin);
}

int main(int argc, char* rcvg[]) {

    FILE* f1 = fopen(rcvg[1], "r");
    yyin = f1;
    yyparse();

}