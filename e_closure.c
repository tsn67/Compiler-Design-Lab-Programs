#include <stdio.h>
#include <stdlib.h>

struct Transition {
    char label;
    int state;
};

struct State {
    int t_count;
    struct Transition trans[100];
};

struct State states[100];
int n;

void push(int s[], int* top, int v) {
    *top = *top + 1;
    s[*top] = v;
}

int pop(int s[], int* top) {
    int t = s[*top];
    (*top)--;  
    return t;
}

int isEmpty(int* top) {
    return *top == -1;
}

int size(int* top) {
    return *top + 1;
}

int contains(int t[], int v, int l) {
    for (int i = 0;i < l;i++)
        if (t[i] == v)
            return 1;
    return 0;
}

void e_closure() {

    for (int i = 0;i < n;i++) {
        int stack[100];
        int top = -1;

        int vis[100];
        int pt = 0;
        push(stack, &top, i);

        while (!isEmpty(&top)) {
            int last = pop(stack, &top);
            vis[pt] = last;
            pt++;

            int t_count = states[last].t_count;
            for (int j = 0;j < t_count;j++) {
                if (states[last].trans[j].label == 'e') {
                    int to = states[last].trans[j].state;

                    if (!contains(stack, to, top + 1) && !contains(vis, to, pt)) {
                        push(stack, &top, to);
                    }
                }
            }
        }

        printf("E-closure(%d): ", i);
        for (int j = 0;j < pt;j++)
            printf("%d ", vis[j]);
        printf("\n");
    }
}

void display() {
    printf("\nE-NFA: \n");
    for (int i = 0;i < n;i++) {
        printf("%d: ", i);
        for (int j = 0;j < states[i].t_count;j++)
            printf("(%d %c) ", states[i].trans[j].state, states[i].trans[j].label);
        printf("\n");
    }
}

void input() {
    scanf("%d", &n); //no of states
    for (int i = 0;i < n;i++) {
        scanf(" %d", &states[i].t_count);
        for (int j = 0;j < states[i].t_count;j++) {
            scanf(" %d", &states[i].trans[j].state);
            scanf(" %c", &states[i].trans[j].label);
        }
    }
}

int main() {
    input();
    display();
    e_closure();
}