#include <stdio.h>
#include <string.h>

struct Tail {
    char tail[100];
};

struct Production {
    char head;
    int tCount;
    struct Tail tails[100];
};

char stack[100];
int top = -1;

void push(char c) {
    top++;
    stack[top] = c;
}

int isEmpty() {
    return top == -1;
}

int size() {
    return top + 1;
}

void add_to_str(char *s, char c) {
    while (*s != '\0')
        s++;
    *s = c;
    *(s + 1) = '\0'; 
}

int n; //productions count
struct Production prodns[100];

int parse(char* input) {

    printf("Stack\t\tInput buffer\t\tAction\n");

    while (1) {

        for (int i = 0;i < size();i++) {
            printf("%c", stack[i]);
        }

        if (isEmpty())
            printf("-");
        if (strlen(input) != 0) 
            printf("\t\t%s\t\t", input);
        else printf("\t\t-\t\t");

        if (*input == '\0' && size() == 1 && stack[top] == 'S')
            return 1;

       int reduced = 0;

        if (!isEmpty()) {

            for (int i = 0;i < size();i++) {

                char temp[100];
                strcpy(temp, "");

                for (int j = i;j < top + 1;j++) {
                    add_to_str(temp, stack[j]);
                }

                for (int j = 0;j < n;j++) {
                    for (int k = 0;k < prodns[j].tCount;k++) {
                        if (strcmp(prodns[j].tails[k].tail, temp) == 0) {
                            printf("reduce\n");
                            reduced = 1;
                            top = i - 1;
                            push(prodns[j].head);
                            break;
                        }
                    }

                    if (reduced == 1)
                        break;
                }

                if (reduced == 1)
                    break;
            }

        }

        //shift
        if (reduced == 0) {
            if (*input != '\0') {
                printf("shift\n");
                push(*input);
                input++;
            } else return 0;
        }

    }

    return 0; 
}

int main() {

    //grammar
    /*
        S -> S + S | S * S | a
    */

    n = 1;
    prodns[0].head = 'S';
    prodns[0].tCount = 3;
    strcpy(prodns[0].tails[0].tail, "S+S");
    strcpy(prodns[0].tails[1].tail, "S*S");
    strcpy(prodns[0].tails[2].tail, "a");

    printf("Enter the input: ");
    char input[100];
    scanf("%s", input);

    int isValid = parse(input);

    if (isValid) {
        printf("\nSucessful Parse!\n");
    } else printf("\nSyntax Error!\n");

}