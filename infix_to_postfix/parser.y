%{
    #include <stdio.h>
    #include <string.h>
%}

%union {
    int num;
    char str[100];
}

%token END
%token<num> DIGIT 
%token<str> IDENT
%type<str> E T F 

%left '+' '-'
%left '*' '/'

%%
S: E END { printf("postfix: %s\n", $1); return 1; }
;
E: E '+' T { sprintf($$, "%s%s+", $1, $3); }
| E '-' T { sprintf($$, "%s%s-", $1, $3); }
| T { strcpy($$, $1); }
;
T: T '*' F { sprintf($$, "%s%s*", $1, $3); }
| T '/' F { sprintf($$, "%s%s/", $1, $3); }
| F { strcpy($$, $1); }
;
F: '(' E ')' { strcpy($$, $2); }
| IDENT { strcpy($$, $1); }
| DIGIT { sprintf($$, "%d", $1); }
;


%%

void yyerror(char* s) {
    printf("Syntax Error!");
    yyrestart(stdin);
}

int main() {

    while (1) {
        printf("Enter infix expression: ");
        yyparse();
    }
}