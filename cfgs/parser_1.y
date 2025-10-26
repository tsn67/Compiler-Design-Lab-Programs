%{
#include <stdio.h>
%}

%union {
    char str[100];
}

%token END
%token<str> A B

%%

S: A B END { 
    if (strlen($1) > (2 * strlen($2))) {
        printf("Valid\n");

    } else printf("Invalid!\n");
    return 1;
}
| A END { printf("Valid!\n"); return 1; }
;

%%

void yyerror(char* s) {
    printf("Invalid\n");
}

int main() {
    while (1) {
        printf(">");
        yyparse();
    }
    return 0;
}
