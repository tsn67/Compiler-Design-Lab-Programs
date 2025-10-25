#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REG_COUNT 8 //8 registers (R0 - R8)
#define ADDR_SIZE 10 //size of address desc

struct ThreeCode {
    char a;
    char b;
    char op;
    char res;
};

int n;
struct ThreeCode input_code[100];

struct Register {
    int reg_id;
    int is_free;
};

//register descriptor operations
struct Register registers[REG_COUNT];

void initialize_regs() {
    for (int i = 0; i < REG_COUNT;i++)
        registers[i].is_free = 1;
}

void free_reg(int id) {
    registers[id].is_free = 1;
}

int use_reg(int id) {
    registers[id].is_free = 0;
}

int get_free_reg() {
    for (int i = 0;i < REG_COUNT;i++)
        if (registers[i].is_free)
            return i;
    return -1; //unhandled
}

struct Address_desc {
    char value;
    int reg_id;
};

struct Address_desc* addr_desc[ADDR_SIZE];

void add_address_desc(char value, int reg_id) {
    for (int i = 0;i < ADDR_SIZE;i++) {
        if (addr_desc[i] == NULL) {
            struct Address_desc* te;
            te = (struct Address_desc*)malloc(sizeof(struct Address_desc));
            te->value = value;
            te->reg_id = reg_id;
            addr_desc[i] = te;
            use_reg(reg_id);
            break;
        }
    }
}

int get_reg(char value) {
    
    for (int i = 0;i < ADDR_SIZE;i++) {
        struct Address_desc* te = addr_desc[i];
        if (te != NULL && te->value == value)
            return te->reg_id;
    }

    return -1; //if not in address_desc
}

void remove_from_addrdesc(char value) {
    int t = get_reg(value);

    //or can directly remove the address descriptor with value = value (arg)
    if (t != -1) {
        for (int i = 0;i < ADDR_SIZE;i++) {
            struct Address_desc* te = addr_desc[i];
            if (te != NULL && te->reg_id == t) {
                free(addr_desc[i]);
                addr_desc[i] = NULL;
                free_reg(t);
                break;
            }
        }
    }
}

void allocate_reg(char value) {
    int r = get_free_reg();
    use_reg(r);
    add_address_desc(value, r);
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}


int has_furthur_ref(int offset, char c) {

    for (int i = offset;i < n;i++) {
        if (input_code[i].a == c || input_code[i].b == c)
            return 1;
    }

    return 0;
}

void remove_unwanted_values(int offset) {

    for (int i = 0; i < ADDR_SIZE;i++) {
        if (addr_desc[i] != NULL && !has_furthur_ref(offset, addr_desc[i]->value))
            remove_from_addrdesc(addr_desc[i]->value);
    }

}

int generate_target_code() {

    for (int i = 0;i < n;i++) {

        char a = input_code[i].a;
        char b = input_code[i].b;
        char res = input_code[i].res;
        char op = input_code[i].op;

        int r = get_reg(a);
        if (r == -1) {
            r = get_free_reg();
            if (is_digit(a)) {
                printf("MOV R%d, #%c\n", r, a);
            } else {
                printf("MOV R%d, %c\n", r, a);
                add_address_desc(a, r);
            }
        } 

        char OPCODE[20];

        switch (op) {
            case '+':
                strcpy(OPCODE, "ADD");
                break;
            case '-':
                strcpy(OPCODE, "SUB");
                break;
            case '*':
                strcpy(OPCODE, "MUL");
                break;
            case '/':
                strcpy(OPCODE, "DIV");
                break;
            default:
                strcpy(OPCODE, "-");
                break;
        }

        if (is_digit(b))
            printf("%s R%d, #%c\n", OPCODE, r,b);
        else {
            int s = get_reg(b);
            if (s != -1)
                printf("%s R%d, R%d\n", OPCODE, r, s);
            else printf("%s R%d, %c\n", OPCODE, r, b);
        }

        remove_from_addrdesc(a);
        remove_from_addrdesc(res); //old values in Registers
        add_address_desc(res, r);

        remove_unwanted_values(i + 1);
    }
}


int main() {

    n = 0;
    // FILE* f1 = fopen("input.txt", "r");

    // int i = 0;
    // while (fscanf(f1, " %c %c %c %c\n", &input_code[i].res, &input_code[i].a, &input_code[i].op, &input_code[i].b) != EOF) {
    //     i++;
    // }
    // n = i;

    scanf("%d", &n);
    for (int i = 0;i < n;i++) {
        scanf(" %c %c %c %c", &input_code[i].res, &input_code[i].a, &input_code[i].op, &input_code[i].b);
    }

    initialize_regs();
    generate_target_code();
}