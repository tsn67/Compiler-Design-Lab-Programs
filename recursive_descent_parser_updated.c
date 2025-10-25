#include <stdio.h>
#include <string.h>

/*
    S -> ABC
    A -> aA | e
    B -> b | bB
    C -> c
*/

char* input;

int S();
int A();
int B();
int C();

int S() {
    if (A())
        if (B())
            if (C())
                return 1;
    return 0;
}

int A() {

    if (*input == 'a') {
        char* te = input;
        input++; 
        if (A())
            return 1;
        else {
            input = te;
        }
    }
        
    return 1;
}

int B() {
    if (*input == 'b') {
        char* te = input;
        input++;
        if (B()) {
            return 1;
        }
        return 1;
    }

    return 0;
}

int C() {
    if (*input == 'c') {
        input++;
        return 1;
    }
    return 0;
}

int parse() {
    return S() && *input == '\0';
}

int main() {
    char str[100];
    printf("Enter the input:");
    scanf("%s", str);
    input = str;

    int isValid = parse();
    if (isValid)  
        printf("Accepted!\n");
    else printf("Syntax Error!\n");
}