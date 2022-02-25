#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

int main()
{
    float f[3][3];
    float f2[3][3];

    f[0][0] = 1.1;
    f[0][1] = 1.2;
    f[0][2] = 1.3;
    f[1][0] = 2.1;
    f[1][1] = 2.2;
    f[1][2] = 2.3;
    f[2][0] = 3.1;
    f[2][1] = 3.2;
    f[2][2] = 3.3;

    long r = syscall(448, f, f2);
    printf("Syscall returned: %ld", r);

    for(int i=0;i<3;++i){
        printf("\n");
        for(int j=0;j<3;++j){
            printf("%f\t", f2[i][j]);
        }
    }
    printf("\n");
    return 0;
}