#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

struct Follow {
    char head;
    char follow[100];
};

int n;
struct Production prodns[100];
struct First firsts[100];
struct Follow follows[100];

void initialize_first() {
    for (int i = 0;i < n;i++) {
        firsts[i].head = prodns[i].head;
        strcpy(firsts[i].first, "");
    }
}

void initialize_follow() {
    for (int i = 0;i < n;i++) {
        follows[i].head = prodns[i].head;
        strcpy(follows[i].follow, "");
    }
    add_to_str(follows[0].follow, '$');
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


int add_helper(char* t, char* s) {
    int v = 0;
    while (*s != '\0') {
        if (!contains(t, *s) && *s != '#') {
            v = 1;
            add_to_str(t, *s);
        }
        s++;
    }
    return v;
}

void calc_follow() {

    int changed = 1;
    while (changed) {
        changed = 0;

        for (int i = 0;i < n;i++) {
            char head = prodns[i].head;

            for (int j = 0;j < n;j++) {
                for (int k = 0;k < prodns[j].t_count;k++) {

                    char* tail = prodns[j].tails[k].tail;

                    while (*tail != '\0') {
                        if (*tail == head) {
                            char* rem = tail + 1;
                            int can_stop = 0;
                            while (*rem != '\0') {
                                if (!isupper(*rem)) {
                                    can_stop = 1;
                                    if (!contains(follows[i].follow, *rem)) {
                                        changed = 1;
                                        add_to_str(follows[i].follow, *rem);
                                    }
                                } else {

                                    //search the first of *rem
                                    for (int l = 0;l < n;l++) {
                                        if (*rem == firsts[l].head) {
                                            if (!contains(firsts[l].first, '#'))
                                                can_stop = 1;
                                            int te = add_helper(follows[i].follow, firsts[l].first);
                                            if (te) {
                                                changed = 1;
                                            }
                                        }
                                    }

                                }
                                if(can_stop)
                                    break;
                                rem++;
                            }
                            if (can_stop == 0) {
                                int v = add_helper(follows[i].follow, follows[j].follow);
                                if (v)
                                    changed = 1;
                            }
                        }
                        tail++;
                    }

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


void display_follow_set() {
    printf("\nFollow: \n");
    for (int i = 0;i < n;i++) {
        printf("%c : ", prodns[i].head);
        char* t = follows[i].follow;

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
    initialize_first();

    calc_firsts();
    display_first_set();

    initialize_follow();
    calc_follow();
    display_follow_set();

}