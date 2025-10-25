#include <stdio.h>
#include <ctype.h>
#include <string.h>

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    return 0;
}

void add_to_str(char* res, char c) {
    while (*res != '\0')
        res++;
    *res = c;
    *(res + 1) = '\0';
}

char stack[100];
int top = -1;

void push(char c) {
    top++;
    stack[top] = c;
}

char pop() {
    char c = stack[top];
    top--;
    return c;
}

int isEmpty() {
    return top == -1;
}

void convert_infix_to_postfix(char* input, char* res) {

    while (*input != '\0') {

        if (isalnum(*input)) {
            add_to_str(res, *input);
        } else {
            if (*input == '(') {
                push('(');
            } else if (*input == ')') {
                while (stack[top] != '(') {
                    add_to_str(res, stack[top]);
                    pop();
                }
                pop();
            } else {
                //operator
                char c = *input;
                while (!isEmpty() && stack[top] != '(' && precedence(stack[top]) >= precedence(c)) {
                    char t = pop();
                    add_to_str(res, t);
                }
                push(c);
            }
        }

        input++;
    }

    while (!isEmpty()) {
        char t = pop();
        add_to_str(res, t);
    }

}

void generate_3_address_code(char* res) {

    top = -1; //reset the stack
    int r = 110;

    printf("\n3 address code\n\n");

    while (*res != '\0') {
        char c = *res;
        if (isalnum(c)) {
            push(c);
        } else {
            char b = pop();
            char a = pop(); 

            printf("%c = %c %c %c\n", r, a, c, b);
            push(r);
            r++;

        }
        res++;
    }

}


int main() {

    // printf("%d", isEmpty());
    char input[100];
    printf("Enter the expression: ");
    scanf("%s", input);

    char result[100];
    strcpy(result, "");
    convert_infix_to_postfix(input, result);
    printf("postfix: %s\n", result);

    generate_3_address_code(result);
}