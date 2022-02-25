#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void createMatrix(int cols[], int rows){
	int **dp;
	int *p[rows];		//Since the matrix has 6 rows

	srand(time(0));
	dp = &p;
	printf("The desired matrix with random values:\n");
	for (int i = 0; i < rows; ++i)
	{
		p[i] = (int*)calloc(cols[i],sizeof(int));
		for (int j = 0; j < cols[i]; ++j)
		{
			*(p+i) = rand() % 10 + 1;
			printf("%d\t", *(p+i));
		}
		printf("\n");
		// free(p[i]);
	}

}


void partA()		//Function for part (a) of the question
{
	int no_of_columns[6] = {7,4,6,3,7,2};		//Since the matrix has 6 rows

	createMatrix(no_of_columns, 6);
}

void partB()		//Function for part (b) of the question
{
	int r, c[50];
	printf("\nEnter the number of rows in the matrix: ");
	scanf("%d", &r);
	for (int i = 0; i < r; ++i)
	{
		printf("No of columns in row %d: ", i+1);
		scanf("%d", &c[i]);
	}

	createMatrix(c, r);
}

int main()
{
	partA();
	partB();
	return 0;
}