/* 
	E -> TE'
	E' -> +TE' | #
	T -> FT'
	T' -> *FT' | #
	F -> (E) | NUM
*/

#include <stdio.h>
#include <string.h>

int T();
int E();
int Z();
int Y();
int F();


char* input;

//E' - Z
//T' - Y

int E() {
	int val = T();
	if (val == 1) {
		val = Z();
	} else return 0;
	
	if (val == 1) 
		return 1;
	return 0;
}


int Z() {
	if (*input == '+') {
		input++;
		int val = T();
		
		if (val == 1) {
			val = Z();
		} else return 0;
		
		if (val == 1) return 1;
		return 0;
	} 
	
	return 1;
}

int T() {
	int val = F();
	
	if (val == 1) {
		val = Y();
		
		if (val == 1)
			return 1;
	}
	
	return 0;

}

int F() {
	if (*input == '(') {
		input++;
		int val = E();
		if (val == 1) {
			if (*input == ')') {
				input++;
				return 1;
			} else return 0;
		} 
		return 0;
	} else {
		//printf("Hello %s", input);
		char c = *input;
		if ('0' <= c && c <= '9') {
			input++;
			return 1;
		}
		//return 0;
	
	}
	
	return 0;
	
}


int Y() {
	if (*input == '*') {
		input++;
		int val = F();
		
		if (val == 1) {
			val = Y();
			if (val == 1)
				return 1;
			else return 0;
		} else return 0;
	} 
	return 1;
}

int main() {
	
	char temp[100];
	
	printf("Enter the input: ");
	scanf("%s", temp);
	
	input = temp;
	int isValid = E();
	if (isValid == 1) {
		if (*input != '\0') {
			printf("Not Valid\n");
			return 0;
		}
		printf("Valid!\n");
	} else {
		printf("Not Valid!\n");
	}

}