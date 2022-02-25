#include <stdio.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/signal.h>
#include<sys/time.h>



void sigalrm_handler(int signum){
	printf("\nInside the SIGALRM handler of E1\n");
  // sleep(2);
}

int main(int argc, char const *argv[])
{
  // sleep(2);
  // printf("\nInside program E1\n");
  printf("\nDestination Process ID for invoking SIGTERM from inside program E1: %d\n", atoi(argv[0]));

  // printf("\nGenerating a random number\n");
  int randomNo;
  __asm__(
      "rdrand  %[randomNo]"
      : [randomNo] "=r" (randomNo)         
  );

  printf("The random number generated is: %d\n", randomNo);  

  char *str;
  str = "\nMessage\n";
  // printf("%s", str);
  union sigval sigdata;
  sigdata.sival_int = randomNo;
  // sigdata.sival_ptr = (void*)str;

  // printf("\nUsing the sigqueue system call to invoke SIGTERM's handler defined in S1\n");
  sigqueue (atoi(argv[0]), SIGTERM, sigdata);
  sleep(2);

  // printf("\nUsing the sigqueue system call to invoke SIGTERM's handler defined in S1\n");
  // sigqueue (atoi(argv[0]), SIGTERM, sigdata);
  // sleep(2);

  // printf("\nRegistering the handler for SIGALRM\n");
  if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
  struct itimerval tim;  // for setting values of itimer
  // signal(SIGALRM,sigalrm_handler);
  // printf("Using the setitimer system call to invoke SIGALRM's handler 5 times each after an interval of 3 seconds\n\n");
  
  tim.it_value.tv_sec = 1;
  tim.it_value.tv_usec = 0;   
  tim.it_interval.tv_sec=3;
  tim.it_interval.tv_usec=0;
  if (setitimer(ITIMER_REAL, &tim, NULL) == -1){
    perror("error calling setitimer()");
    exit(1);
  }

  int i=0;
  while (i<5) {
    i++;
    pause();
  }
  pause();
  // sleep(3);
}




  
