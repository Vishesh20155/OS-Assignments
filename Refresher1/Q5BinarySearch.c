#include<stdio.h>
#include<stdlib.h>

int bianrySearch(long long a[], int n, long x){
	int f = 0;
	int l = n-1;
	int ans = -1;
	int m;
	while(f<=l){
		m = f + (l-f)/2;
		if(a[m] == x){
			ans = m;
			return ans;
		}

		else if(a[m] > x){
			l = m-1;
		}

		else{
			f = m+1;
		}

	}
	return ans;
}

int comparator (const void * a, const void * b)
{
    if( *(long long int*)a - *(long long int*)b < 0 )
        return -1;
    if( *(long long int*)a - *(long long int*)b > 0 )
        return 1;
    return 0;
}

int main()
{
	long long a[1000];
	int n;
	printf("Enter the no. of elements in the array: ");
	scanf("%d", &n);

	printf("Enter the array: ");

	for (int i = 0; i < n; ++i)
	{
		scanf("%lld", &a[i]);
	}
	long long x;
	printf("Enter the element you wish to search: ");	
	scanf("%lld", &x);

	qsort((void*)a, n, sizeof(a[0]), comparator);
	printf("\nArray after sorting: ");
	
	for (int i = 0; i < n; ++i) 
    	printf("%lld ", a[i]); 

    int ans = bianrySearch(a, n, x);
    if (ans == -1){
    	printf("\nElement not found\n");
    }
    else{
    	printf("\nElement found at index = %d of the sorted array(0-based indexing)\n", ans);
    }
   

	return 0;
}