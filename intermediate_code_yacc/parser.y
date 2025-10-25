%{
    #include <stdio.h>   
    #include <string.h>
    int n = 0;

    void get_str(char* str, int n) {
        sprintf(str, "t%d", n);
    }

    int print_3_code(char* f, char op, char* s) {
        printf("t%d %c %s %s\n", n, op, f, s);
        n++;
        return n - 1;
    }

%}

%union {
    char str[100];
}

%token<str> NUM VAR END
%type<str> E T F

%left '-' '+'
%left '*' '/'

%%

S: E END { return 1; }
;
E: E '+' T { get_str($$, print_3_code($1, '+', $3)); }
| E '-' T { get_str($$, print_3_code($1, '-', $3)); }
| T { strcpy($$, $1); }
;
T: T '*' F { get_str($$, print_3_code($1, '*', $3)); }
| T '/' F  { get_str($$, print_3_code($1, '/', $3)); }
| F { strcpy($$, $1); }
;
F: '(' E ')' { strcpy($$, $2); }
| NUM { strcpy($$, $1); }
| VAR { strcpy($$, $1); }
;

%%

void yyerror(char* s) {

}

int main() {
    printf("Enter the expression: ");
    yyparse();
}