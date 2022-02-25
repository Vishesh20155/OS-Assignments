#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/signal.h>
#include <sys/time.h>


void sigterm_handler(int signum, siginfo_t *info, void *c){
	int len = strlen("Inside the SIGTERM's signal handler of S1\n");
	int w = write(fileno(stdout), "Inside the SIGTERM's signal handler of S1\n", len);
	if(w<0){
		perror("Unable to write in stdout");
		exit(1);
	}
	printf("The number passed in the SIGTERM handler is: %d\n", info->si_value);
	printf("The string passed in the SIGTERM handler is: %s\n", (char*)info->si_ptr);
	
	sleep(2);
	pause();
}

void S1(){
	printf("\nInside S1 i.e. child process of Main Program\n");
	printf("Registering the signal handler for SIGTERM.\n");
	// signal(SIGTERM,sigterm_handler); 
	struct sigaction my_action;
	my_action.sa_flags = SA_SIGINFO;
	my_action.sa_sigaction = &sigterm_handler;
	
	sigaction(SIGTERM, &my_action, NULL);		//Declaring the signal handler for SIGTERM
}

void SR(pid_t p)
{
	printf("\nInside SR i.e. child process for calling E1 program\n");
	
	char y[20];
	sprintf(y, "%d", p);			//To convert integer process id to a string y

	printf("Using execl command to transfer control to the program E1\n");
	int err = execl("./e1", y);				//Using execl to pass a parameter to Program E1
	if(err<0){
		perror("Error calling execl");
		exit(1);
	}
}

void ST(pid_t p)
{
	printf("\nInside ST i.e. child process for calling E2 program\n");
	
	char y[20];
	sprintf(y, "%d", p);			//To convert integer process id to a string y

	printf("Using execl command to transfer control to the program E2\n");
	int err = execl("./e2", y);				//Using execl to pass a parameter to Program E1
	if(err<0){
		perror("Error calling execl");
		exit(1);
	}
}


int main(){
	pid_t pid;
	
	printf("Forking for the first time... \n");
	if((pid=fork())<0){
		perror("Error in calling Fork system call\n");
		exit(1);
	}

	else if(pid==0){
		S1();
		int err = pause();			//Waiting to catch a signal
		if(err<0){
			perror("Error in pause system call");
			exit(1);
		}
	}

	else{
		sleep(2);
		printf("\nInside the parent of the Main Program after registering signal handler for SIGTERM\n");
		printf("Destination Process ID for kill/sigqueue is: %d\n", pid);
		
		pid_t pidSR, pidST;
		printf("Forking for the second time... \n");
		if((pidSR=fork())<0){
			perror("Error in calling Fork system call\n");
			exit(1);
		}

		else if(pidSR==0){
			SR(pid);
			printf("here\n");
			pause();
			// exit(0);
		}

		else{
			int s;
			waitpid(pidSR, &s, 0);
			// S1();
			sleep(2);
			// pause();
			printf("\nBack inside the parent of the Main Program after transferring control of child to E1\n");
			
			
			printf("Forking for the third time... \n");
			if((pidST=fork())<0){
				perror("Error in calling Fork system call\n");
				exit(1);
			}

			else if(pidST==0){
				ST(pid);
			}

			else{
				int s;
				waitpid(pidST, &s, 0);
				printf("\nBack inside the parent of the Main Program after transferring control of child to E2\n");
			}
		}


		// union sigval sigdata;
		// sigdata.sival_int = 5;
		
		// printf("Using the sigqueue system call to invoke SIGTERM's handler\n");
		// sigqueue (pid, SIGTERM, sigdata);
		// sleep(2);
		// printf("Using the kill system call to invoke SIGTERM's handler\n");
		// kill(pid,SIGTERM);
	}
	// return 0;
}