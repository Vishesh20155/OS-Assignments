#include<stdio.h>
#include "functionC.c"

extern void functionB(unsigned long);

void A(){
    unsigned long int x;
    printf("Program Control is currently inside function A\n");
    printf("Enter the 64 bit integer: ");
    scanf("%ld", &x);
    printf("\n");
    printf("Transferring control to function B.....\n");
    
    functionB(x);
    printf("This line won't be printed\n");  //This line is not printed indicating that the program does not ever return to A()
}

int main(int argc, char const *argv[])
{
    printf("");
    A();
    return 0;
}

