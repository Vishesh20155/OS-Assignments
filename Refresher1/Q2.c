#include <stdio.h>
#include <string.h>

void Stringreverse(char s[]){
	int len = strlen(s);
	char c;
	for (int i = 0; i < len/2; ++i)
	{
		c = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = c;
	}
}

void addBinary(char a[], char b[], char res[]){
	int i=0;
	int flag=0;
	int na=strlen(a);
	int nb=strlen(b);

	while((i<na) && (i<nb)){
		res[i] = ((a[i]-'0')^(b[i]-'0')^flag) + '0';
		flag = ((a[i]-'0')&(b[i]-'0')) | ((a[i]-'0')&flag) | ((b[i]-'0')&flag);
		i++;
	}

	while(i<na){
		res[i] = ((a[i]-'0')^('0'-'0')^flag) + '0';
		flag = ((a[i]-'0')&('0'-'0')) | ((a[i]-'0')&flag) | (('0'-'0')&flag);
		i++;
	}
	while(i<nb){
		res[i] = (('0'-'0')^(b[i]-'0')^flag) + '0';
		flag = (('0'-'0')&(b[i]-'0')) | (('0'-'0')&flag) | ((b[i]-'0')&flag);
		i++;
	}
	if(flag == 1)
		res[i]='1';
}

void removeFirst(char a[]){
	char res[100];
	strcpy(res, "");
	for (int i = 1; i < strlen(a); ++i)
	{
		res[i-1] = a[i];
	}
	strcpy(a, res);
}


void divBy2(char a[]){
    int k=0;
	
	int x, flag=0;
	char chp;

	for (int i = 0; i < strlen(a); ++i)
	{
		x = a[i] - '0';
		if(flag == 1)
			x=x+10;

		if (x%2 == 1)
			flag=1;
		else
			flag=0;

		x = x/2;
		chp = x+'0';
		a[k++] = chp;
	}
	
}

int main()
{
	char a[100], ip2[100], b[300], jlk[300]="";
	char str2[300] = "";
	int binary[300];

	printf("First Number: ");
	scanf("%s", a);
	

	for (int i = 0; i < 100; ++i)
	{
		b[i] = '0';
	}

	int x=0;

	while(strcmp(a, b)>0){
		binary[x++] = (a[strlen(a)-1]%2);
		divBy2(a);
	}

	for (int i = 0; i < x; ++i)
	{
		char ch = binary[x-i-1] + '0';
		jlk[i] = ch;
	}

	printf("Second Number: ");
	scanf("%s", ip2);
	x=0;

	while(strcmp(ip2, b)>0){
		binary[x++] = (ip2[strlen(ip2)-1]%2);
		divBy2(ip2);
	}

	for (int i = 0; i < x; ++i)
	{
		char ch = binary[x-i-1] + '0';
		str2[i] = ch;
	}

	char final_ans[300] = "";

	printf("Binary of first number: %s\n", jlk);
	printf("Binary of first number: %s\n", str2);

	Stringreverse(jlk);
	Stringreverse(str2);

	addBinary(jlk, str2, final_ans);
	Stringreverse(final_ans);

	if(strlen(final_ans) > 256){
		printf("Overflow! Cannot add the numbers.\n");
	}
	else{
		printf("Binary result of Addition of 2 numbers: %s\n", final_ans);
	}
	
	return 0;
}