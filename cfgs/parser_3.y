%{
    #include <stdio.h>   
    #include <string.h>
%}

%union {
    char str[100];
}

%token END
%token<str> ABWORD

%%

S : ABWORD END {
    if (strlen($1) == 0) {
        printf("Valid!\n");
        return 1;
    }

    if (strlen($1) % 2 != 0) {
        printf("Invalid!\n");
        return 1;
    }

    int n = strlen($1);
    for (int i = 0;i < n / 2;i++) {
        if ($1[i] != $1[n - i - 1]) {
            printf("Invalid\n");
            return 1;
        }
    }

    printf("Valid!\n");
    return 1;
}
| END { printf("Valid!\n"); return 1; }
;


%%

void yyerror(char* s) {
    printf("Invalid!\n");
    yyrestart(stdin);
}

int main() {
    while(1) {
        printf(">");
        yyparse();
    }
}