/*

qn: write a lex (or yacc) program to recognize the language => (a|b)a+b*a+(a|b)
here lex alone is sufficient

*/

%{
    #include <stdio.h>
%}

%%

^(a|b)a[a]*[b]*a[a]*(a|b)(\n) { printf("Valid!\n"); }
^.*(\n) { printf("Invalid\n"); }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
}