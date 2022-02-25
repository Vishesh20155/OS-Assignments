#include <stdio.h>

int main(){
	
	char s[100];	//Max length of string is 100 as discussed in tutorial
	printf("Enter the string to be reversed: ");
	gets(s);
	int len = 0;
	for (int i = 0; s[i] != '\0'; ++i)
	{
		len+=1;
	}
	char c;

	for (int i = 0; i < len/2; ++i)
	{
		c = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = c;
	}

	printf("Reversed string: %s \n", s);
	return 0;

}