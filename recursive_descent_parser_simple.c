#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

E → T E'
E' → + T E' | ε
T → F T'
T' → * F T' | ε
F → (E) | d

*/

char* input;

int E();
int T();
int EP();
int F();
int TP();

int E() {
    if (T())
        if (EP())
            return 1;
    return 0;
}

int EP() {
    char* temp = input;

    if (*input == '+') {
        input++;
        if (T())
            if (EP())
                return 1;
    }

    input = temp;
    return 1;
}

int T() {
    if (F())
        if (TP())
            return 1;
    return 0;
}

int TP() {
    char* temp = input;
    if (*input == '*') {
        input++;
        if (F())
            if (TP())
                return 1;
    }

    input = temp;
    return 1;
}

int F() {
    if (*input == '(') {
        input++;
        if (E()) {
            if (*input == ')' ) {
                input++;
                return 1;
            }
        }
    } else if (*input == 'd') {
        input++;
        return 1;
    }
    return 0;
}

int main() {

    while (1) {
        printf("Enter input: ");
        char temp[100];
        scanf("%s", temp);

        input = strdup(temp);

        if (E() && *input == '\0') {
            printf("Valid!\n");
        } else printf("Invalid\n");
    }
}

