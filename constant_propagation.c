#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAP_SIZE 10

struct Map {
    char var[100];
    int value;
};

struct Map* map[MAP_SIZE];

void add_or_update(char* v, int value) {
    //update if present
    for (int i = 0;i < MAP_SIZE;i++) {
        if (map[i] != NULL && strcmp(map[i]->var, v) == 0) {
            map[i]->value = value;
            return;
        }
    }

    //else add
    for (int i = 0;i < MAP_SIZE;i++) {
        if (map[i] == NULL) {
            map[i] = (struct Map*)malloc(sizeof(struct Map));
            map[i]->value = value;
            strcpy(map[i]->var, v);
            return;
        }
    }
}

int contains(char* v) {
    for (int i = 0;i < MAP_SIZE;i++) 
        if (map[i] != NULL && strcmp(v, map[i]->var) == 0)
            return 1;
    return 0;
}

int get_value(char* v) {
    for (int i = 0;i < MAP_SIZE;i++) {
        if (map[i] != NULL && strcmp(map[i]->var, v) == 0)
            return map[i]->value;
    }
}

struct ThreeCode {
    char a[100];
    char b[100];
    char op[100];
    char res[100];
};

int n;
struct ThreeCode input[100];

int is_number(char* v) {
    if (*v == '-') //for -ve numbers
        v++;
    
    while (*v != '\0') {
        if (!(*v <= '9' && *v >= '0'))
            return 0;
        v++;
    }
    return 1;
}


void const_propagate() {

    for (int i = 0;i < n;i++) {
        char* a = input[i].a;
        char* b = input[i].b;
        char* op = input[i].op;
        char* res = input[i].res;

        if (strcmp(b, "-") == 0 && (is_number(a) || contains(a))) {
            if (is_number(a)) {
                add_or_update(res, atoi(a));
            } else {
                add_or_update(res, get_value(a));
                sprintf(input[i].a, "%d", get_value(a));
            }
        } else if (strcmp(b, "-") != 0) {

            if (contains(a)) {
                sprintf(input[i].a, "%d", get_value(a));
            }

            if (contains(b)) {
                sprintf(input[i].b, "%d", get_value(b));
            }

            if (is_number(input[i].a) && is_number(input[i].b)) {
                int r = 0;
                int c = atoi(input[i].a);
                int d = atoi(input[i].b);

                switch(op[0]) {
                    case '+':
                        r = c + d;
                        break;
                    case '-':
                        r = c - d;
                        break;
                    case '*':
                        r = c * d;
                        break;
                    default:
                        r = 0;
                        break;
                }

                strcpy(input[i].b, "-");
                strcpy(input[i].op, "-");
                sprintf(input[i].a, "%d", r);
                add_or_update(input[i].res, r);
            }

        }

    }

}

void print_output() {
    printf("\n\n");
    for (int i = 0;i < n;i++) {
        printf("%s %s %s %s\n", input[i].res, input[i].a, input[i].op, input[i].b);
    }
}


int main() {

    printf("Enter the count: ");
    scanf("%d", &n);

    printf("Enter three-addr code(result, operand1, opeartor, operand2) - (for no value '-'):\n");
    for (int i = 0;i < n;i++) {
        scanf("%s", input[i].res);
        scanf("%s", input[i].a);
        scanf("%s", input[i].op);
        scanf("%s", input[i].b);
    }

    const_propagate();
    print_output();
}