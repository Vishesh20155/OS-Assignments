#include <stdio.h>
#include<stdlib.h>
#include <string.h>

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

int main(int argc, char const *argv[])
{
	int a[100], ch=3, n = argc-2;
	char str[100];

	if (strcmp("bubble", argv[1]) == 0)
	{
		ch=1;
	}
	else if (strcmp("selection", argv[1]) == 0)
	{
		ch=2;
	}
	else{
		printf("Incorrect Choice!!\n");
		exit(0);
	}

	for (int i = 0; i < argc-2; ++i)
	{
		strcpy(str, argv[i+2]);
		a[i] = atoi(str);
	}

	
	if(ch == 1){
		bubble_sort(n, a);
	}
	else if(ch == 2){
		selection_sort(n, a);
	}
	else{
		printf("Incorrect Choice!!");
		exit(0);
	}

	printf("\nSorted Array:\n");

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}	

	printf("\n");

	printf("Sorted using %s sort\n", argv[1]);

	return 0;
}