#include <stdio.h>
#include <stdlib.h>

void readWrite(char src[], char dest[]){
	FILE *p1 = fopen(src, "r");
	
	if(p1 == NULL){
		printf("No file to read - Source file not available!\n");
		return;
	}

	FILE *p2 = fopen(dest, "w");

	char ch;
	while(fread(&ch, sizeof(char), 1, p1)>0){
		// printf("%c", ch);
		fwrite(&ch, sizeof(char), 1, p2);
	}


	fclose(p1);
	fclose(p2);
}

int main()
{
	char src[50], dest[50], c;

	// printf("Are the files in text format (y/n): ")
	// scanf("%c", c);

	printf("\nSource filename: ");
	scanf("%s", src);
	printf("\nDestination filename: ");
	scanf("%s", dest);

	readWrite(src, dest);

	return 0;
}