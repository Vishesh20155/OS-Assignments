#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void add(int a, int b){
	int res = a+b;
	printf("The result is: %d\n", res);
}

void sub(int a, int b){
	int res = a-b;
	printf("The result is: %d\n", res);
}

void mul(int a, int b){
	int res = a*b;
	printf("The result is: %d\n", res);
}

void division(int a, int b){
	float res = (float)a/b;
	printf("The result is: %f\n", res);
}

void exponentiation(int a, int b){
	int res = pow(a, b);
	printf("The result is: %d\n", res);
}

int main()
{
	void (*func_ptr[5])(int, int);
    func_ptr[0] = add;
    func_ptr[1] = sub;
	func_ptr[2] = mul;
	func_ptr[3] = division;
	func_ptr[4] = exponentiation;
	printf("MENU: \n Choose any of the options:\n");
	printf("1. Addition\n");
	printf("2. Subtraction\n");
	printf("3. Multiplication\n");
	printf("4. Division\n");
	printf("5. Exponentiation\n");
	printf("Enter your choice: ");
	int opt;
	scanf("%d", &opt);

	if((opt>5) || (opt<1)){
		printf("\nIncorrect Option Chosen. Try Again.\n\n");
		main();
	}
	else{
		int a, b;
		printf("\nEnter first operand: ");
		scanf("%d", &a);
		printf("Enter second operand: ");
		scanf("%d", &b);
		func_ptr[opt-1](a, b);
	}
	return 0;
}