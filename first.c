#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Tail {
    char tail[100];
};

struct Production {
    char head;
    int t_count;
    struct Tail tails[100];
};

struct First {
    char head;
    char first[100];
};

int n;
struct Production prodns[100];
struct First firsts[100];

void initialize() {
    for (int i = 0;i < n;i++) {
        firsts[i].head = prodns[i].head;
        strcpy(firsts[i].first, "");
    }
}

int contains(char* s, char c) {
    while (*s != '\0') {
        if (*s == c)
            return 1;
        s++;
    }
    return 0;
}

void add_to_str(char* s, char c) {
    if (contains(s, c))
        return;
    while (*s != '\0')
        s++;
    *s = c;
    *(s + 1) = '\0';
}

void first(char head, char* res) {
    if (!isupper(head) || head == '#') {
        add_to_str(res, head);
        return;
    }

    for (int i = 0;i < n;i++) {
        if (head == firsts[i].head) {
            char* t = firsts[i].first;
            while (*t != '\0') {
                add_to_str(res, *t);
                t++;
            }
        }
    }   
}


void calc_firsts() {

    int change = 1;

    while (change == 1) {
        change = 0;
        for (int i = 0;i < n;i++) {
            // char head = prodns[i].head;

            for (int j = 0;j < prodns[i].t_count;j++) {
                char* tail = prodns[i].tails[j].tail;

                while (*tail != '\0') {
                    char te[100];
                    strcpy(te, "");
                    first(*tail ,te);

                    int cont = 0;
                    char* tm = te;
                    while (*tm != '\0') {
                        char c = *tm;
                        if (c == '#') {
                            if (*(tail + 1) == '\0' && !contains(firsts[i].first, '#')) {
                                change = 1;
                                add_to_str(firsts[i].first, '#');
                            }
                            cont = 1;
                        } else {
                            if (!contains(firsts[i].first, c)) {
                                change = 1;
                                add_to_str(firsts[i].first, c);
                            }
                        }
                        tm++;
                    }

                    if (cont == 0)
                        break;
                    else tail++;
                }
            }
        }
    }
}

void display_first_set() {
    printf("\nFirst: \n");
    for (int i = 0;i < n;i++) {
        printf("%c : ", prodns[i].head);
        char* t = firsts[i].first;

        while (*t != '\0') {
            printf("%c ", *t);
            t++;
        }

        printf("\n");
    }
}

void display_grammar() {
    printf("\nGrammar: \n");
    for (int i = 0;i < n;i++) {
        printf("%c -> ", prodns[i].head);
        for (int j = 0;j < prodns[i].t_count;j++) {
            printf(" %s ", prodns[i].tails[j].tail);

            if (j != prodns[i].t_count - 1) {
                printf("|");
            }
        }
        printf("\n");
    }
}

int main() {
    FILE* input = fopen("input.txt", "r");

    char t[100];
    fscanf(input, "%s", t);
    n = atoi(t);

    for (int i = 0;i < n;i++) {
        fscanf(input, "%s", t);
        prodns[i].head = t[0];

        fscanf(input, "%s", t);
        int m = atoi(t);

        prodns[i].t_count = m;
        for (int j = 0;j < m;j++) {
            fscanf(input, "%s", t);
            strcpy(prodns[i].tails[j].tail, t);
        }
    }

    display_grammar();
    initialize();
    calc_firsts();
    display_first_set();
}