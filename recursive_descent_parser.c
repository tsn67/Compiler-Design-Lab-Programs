#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*

E → T E'
E' → + T E' | ε
T → F T'
T' → * F T' | ε
F → (E) | d

*/

int E(char**);
int EP(char**);
int T(char**);
int TP(char**);
int F(char**);

int E(char** input) {
    if (T(input))
        if(EP(input))
            return 1;
    return 0;
}

int EP(char** input) {
    char* temp = *input;
    if (**input == '+') {
        (*input)++;
        if (T(input))
            if (EP(input))
                return 1;
    }
    *input = temp; // reset if + T E' parsing fails.
    return 1;
}

int T(char** input) {
    if (F(input))
        if (TP(input))
            return 1;
    return 0;
}

int TP(char** input) {
    char* temp = *input;
    if (**input == '*') {
        (*input)++;
        if (F(input))
            if (TP(input))
                return 1;
    }
    *input = temp;
    return 1;
}

int F(char** input) {
    char* temp = *input;
    if (**input == 'd') {
        (*input)++;
        return 1;
    } else if (**input == '(') {
        (*input)++;
        if (E(input)) {
            if (**input == ')') {
                (*input)++;
                return 1;
            }
        }
    }
    *input = temp;
    return 0;
}


int main() {
    while (1) {
        printf("Enter the input: ");
        char temp1[100];
        scanf("%s", temp1);

        char* temp2 = temp1;
        char** input;
        input = &temp2;

        if (E(input) && **input == '\0')
            printf("Successful!\n");
        else printf("Invalid\n");
    }
}