#include <stdio.h>
#include<stdlib.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sort(int n, int arr[]){
	for (int i = 0; i < n-1; ++i)
	{
		for (int j = 0; j < n-1-i; ++j)
		{
			if(arr[j] > arr[j+1])
				swap(&arr[j], &arr[j+1]);
		}
	}
}

void selection_sort(int n, int arr[]){
	for (int i = 0; i < n-1; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if(arr[j] < arr[i])
				swap(&arr[i], &arr[j]);
		}
	}
}

int input_choice(){
	int ch;
	scanf("%d", &ch);
	if((ch == 1) || (ch == 2)){
		return ch;
	}
	printf("\nIncorrect input. Try Again.\n");
	printf("Enter your choice: ");
	return input_choice();
}

int main()
{
	int a[100], n, ch = 1;
	printf("Enter the number of elements in the array: ");
	scanf("%d", &n);
	printf("Enter the elements of the array: ");
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);
	}

	printf("Choose any of the options:\n");
	printf("1. Bubble Sort\n");
	printf("2. Selection Sort\n");
	printf("Enter your choice: ");

	ch = input_choice();

	if(ch == 1){
		bubble_sort(n, a);
	}
	else{
		selection_sort(n, a);
	}

	printf("\nSorted Array:\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}	

	printf("\n");

	return 0;
}