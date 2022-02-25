#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/resource.h>
#include <sched.h>

int isPrime(unsigned long long n)
{
    for (int i = 2; i <= n/2; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

void func(){
    long long unsigned c=0, x=2;
    while(c<20000){
        if(isPrime(x) == 1){
            // printf("%llu ", x);
            c++;
        }
        x++;
    }
}

int main(){
    
    long retval = syscall(448, getpid(), 20);

    double start_wo2 = omp_get_wtime();
    func();
    double time_wo2 = omp_get_wtime() - start_wo2;
    printf("Process finished after syscall in %f seconds \n",time_wo2);
    // printf("%d\n", x);

    return 0;
}