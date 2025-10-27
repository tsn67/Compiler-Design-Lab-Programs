/*
    any string using 'a' and 'b' with prefix 'aaaaa' (5 'a's)
*/


%{
    #include <stdio.h>
%}

START [a]{5}
END [ab]*

%%

^{START}{END}$ { printf("Valid!\n"); }
^.*$ { printf("Invalid!\n"); }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
}
