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
#include<assert.h>
#include<time.h>


pid_t pidS1;

unsigned long long getCPUclockCycles(){
  unsigned v1, v2;
  __asm__ __volatile__ ("rdtsc" : "=a"(v1), "=d"(v2));
  return ( (unsigned long long)v1)|( ((unsigned long long)v2)<<32 );
}

void sigterm_handler_in_ST(int signum, siginfo_t *info, void *c){
	printf("\nInside the SIGTERM's signal handler defined in E2\n");
	
  // printf("Printing time's string from inside SIGTERM handler in ST: %s\n", str); 

	// printf("The number passed in the SIGTERM handler is: %d\n", info->si_value);
	printf("The string passed in the SIGTERM handler defined in E2 is: %s\n", (char*)info->si_ptr);
	
	// sleep(1);
}


void sigalrm_handler(int signum){
	printf("Inside the SIGALRM's signal handler defined in program E2\n");
  // printf("Using the rdtsc in inline assemby to find the number of clock ticks since the last reset\n");
  unsigned long long x = getCPUclockCycles();
  printf("No of clock cycles from inside the SIGALRM handler of ST using rdtsc = %llu\n", x);
  printf("Time inseconds elapsed since last reset: %llu seconds", x/1800000000);
  time_t t = time(NULL);
  char* str = ctime(&t);        //ctime gives the current time of the system
     
  union sigval sigdata;
  sigdata.sival_ptr = str;

  // printf("Using the sigqueue to call the SIGTERM's handler defined in ST using the string for time...\n");
  sigqueue(getpid(), SIGTERM, sigdata);  

  // sleep(2);
}

int main(int argc, char const *argv[])
{
  pidS1 = atoi(argv[0]);
  sleep(2);
  // printf("\nInside program E2\n");
  // printf("Destination Process ID for invoking S1's SIGTERM from inside program E2: %d\n", pidS1); 
  
  char *str;
  str = "\nMessage\n";
  // printf("%s", str);
  union sigval sigdata;
  sigdata.sival_int = 5;
  // sigdata.sival_ptr = (void*)str;

  // printf("\nUsing the sigqueue system call to invoke SIGTERM's handler defined in S1\n");
  sigqueue (atoi(argv[0]), SIGTERM, sigdata);
  // sleep(2);
  

  // printf("\nRegistering the handler for SIGALRM\n");
  if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }

  // printf("Registering the handler for ST's SIGTERM\n");
  struct sigaction my_action;
	my_action.sa_flags = SA_SIGINFO;
	my_action.sa_handler = (void (*)(int)) &sigterm_handler_in_ST;
	
	sigaction(SIGTERM, &my_action, NULL);		//Declaring the signal handler for SIGTERM


  struct itimerval tim;  // for setting values of itimer
  // signal(SIGALRM,sigalrm_handler);
  // printf("Using the setitimer system call to invoke SIGALRM's handler 2 times each after an interval of 8 seconds\n\n");
  
  tim.it_value.tv_sec = 2;
  tim.it_value.tv_usec = 0;   
  tim.it_interval.tv_sec=8;
  tim.it_interval.tv_usec=0;
  if (setitimer(ITIMER_REAL, &tim, NULL) == -1){
    perror("error calling setitimer()\n");
    exit(1);
  }

  int i=0;
  while (i<2) {
    ++i;
    pause();
  }
  
  tim.it_value.tv_sec = 0;
  tim.it_value.tv_usec = 0;   
  pause();

  // kill(getpid(), SIGTERM);
}
