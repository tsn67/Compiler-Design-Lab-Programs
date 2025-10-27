#include <string.h>
#include <stdio.h>
#include <ctype.h>


/*
    lexical analyzer using c
    just identify the valid tokens (no symbol table making)
    *not detect lexical errors 

    input: keywords.txt, code.c
*/

char* keywords[100];
int k_count = 0;

void read_keywords() {
    FILE* f1 = fopen("keywords.txt", "r");
    char temp[100];

    while (fscanf(f1, "%s", temp) != EOF) {
        keywords[k_count] = strdup(temp);
        k_count++;
    }
}

int main() {

    read_keywords();
    FILE* f1 = fopen("code.c", "r");
    char c;

    while (fscanf(f1, "%c", &c) != EOF) {
        if (c == '/') {
            fscanf(f1, "%c", &c);
            if (c  == '/') {
                while ( fscanf(f1, "%c", &c) != EOF && c != '\n') {
                }
            } else {
                ungetc(c, f1);
            }
        } else if (isalnum(c) || c == '\"' || c == '\'') {
            if (c == '\"') {
                char temp[100];
                char* t = temp;
                while (fscanf(f1,"%c",  &c) != EOF && c != '\"') {
                    *t = c;
                    t++;
                }
                *t = '\0';
                printf("String Literal: %s\n", temp);
            } else if (c == '\'') {
                fscanf(f1, "%c", &c);
                printf("Char Literal: %c\n", c);
                fscanf(f1, "%c", &c);
            } else if (isdigit(c)) {
                char temp[100];
                char* t = temp;
                *t = c;
                t++;
                while (fscanf(f1, "%c", &c) != EOF && isdigit(c)) {
                    *t = c;
                    t++;
                }
                *t = '\0';
                printf("Number Literal: %s\n", temp);
                ungetc(c, f1);
            } else {

                char temp[100];
                char* t = temp;

                *t = c;
                t++;
                while (fscanf(f1, "%c", &c) != EOF && isalnum(c)) {
                    *t = c;
                    t++;
                }
                *t = '\0';

                int is_key_word = 0;
                for (int i = 0;i < k_count;i++) {
                    if (strcmp(keywords[i], temp) == 0) {
                        is_key_word = 1;
                        printf("Keyword: %s\n", temp);
                    }
                }

                if (!is_key_word)
                    printf("Identifier: %s\n", temp);
                ungetc(c, f1);
            }
        } else if (c == ' ' || c == '\n')
            continue;
        else {
            printf("Special Symbol: %c\n", c);
        }
    } 


}