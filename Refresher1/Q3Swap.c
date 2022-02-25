#include <stdio.h>

void swap(int *x, int *y){
	int t = *x;
	*x = *y;
	*y = t;
}

void var(){
	int a, b;
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);

	printf("\nBefore Swapping:\n");
	printf("\ta = %d\n\tb = %d", a, b);

	swap(&a, &b);

	printf("\n\nAfter Swapping:\n");
	printf("\ta = %d\n\tb = %d\n", a, b);

}

void arr(){
	int a[100], b[100], xa, xb;
	printf("Enter the number of elements in array A: ");
	scanf("%d", &xa);
	printf("Enter array A: ");
	for (int i = 0; i < xa; ++i)
	{
		scanf("%d", &a[i]);
	}

	printf("Enter the number of elements in array B: ");
	scanf("%d", &xb);
	printf("Enter array B: ");
	for (int i = 0; i < xb; ++i)
	{
		scanf("%d", &b[i]);
	}

	printf("\nBefore Swapping:\n");
	printf("array A: ");
	for (int i = 0; i < xa; ++i)
	{
		printf("%d ", a[i]);
	}

	printf("\narray B: ");
	for (int i = 0; i < xb; ++i)
	{
		printf("%d ", b[i]);
	}

	swap(&xa, &xb);
	int len = xa>xb?xa:xb;

	for (int i = 0; i < len; ++i)
	{
		swap(&a[i], &b[i]);
	}

	printf("\n\nAfter Swapping:\n");
	printf("array A: ");
	for (int i = 0; i < xa; ++i)
	{
		printf("%d ", a[i]);
	}

	printf("\narray B: ");
	for (int i = 0; i < xb; ++i)
	{
		printf("%d ", b[i]);
	}

	printf("\n");

}

int main(int argc, char const *argv[])
{
	char c;
	printf("Do you wish to swap Arrays(A and B) or Variables(a and b)?\nEnter \'A\' for Arrays and 'V' for variables: ");
	scanf("%c", &c);

	if(c == 'A'){
		arr();
	}
	else if(c == 'V'){
		var();
	}

	else{
		printf("\nInvalid Input!");
	}

	return 0;
}