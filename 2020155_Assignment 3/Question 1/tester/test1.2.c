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
#include<linux/sched.h>
#include <sys/resource.h>
#include<sched.h>

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

    // pid_t p = fork();
    // int s;
    struct timespec *tp;
    int k = nice(19);
    if(k==-1){
        printf("couldn't change\n");
    }

    int which = PRIO_PROCESS;
    int ret = getpriority(which, getpid());
    printf("NICE VAL: %d\n", ret);

    double start_wo = omp_get_wtime();
    func();
    double time_wo = omp_get_wtime() - start_wo;

    printf("Process finished in %f seconds without the SYSCALL\n",time_wo);

    long retval = syscall(448, getpid(), 20);
    printf("Syscall Returned: %ld\n", retval);
    
    printf("%d\n", getpid());
    execl("./t2.2", NULL);
    
    return 0;
}