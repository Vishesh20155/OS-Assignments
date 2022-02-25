#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<string.h>
#include<sys/wait.h>
#include <pthread.h>

char line_content[100][100];
int line_no;
int assignment_totalA[100];
int assignment_totalB[100];
int no_of_studentsA=0;
int no_of_studentsB=0;
int no_of_assignments;

void read_from_file(){
	int fd = open("student_record.csv", O_RDONLY); //System Call used-handle error
	//student_record.csv should be in same directory

	if (fd<0)
    {
        printf("Error Number % d\n", errno);
        perror("Program");  
        exit(1);              
    }

    char c;
    int size = 1;
    line_no=0;
    int i=0;
    while(size>0){
        size = read(fd, &c, 1);		//System call used
        if(size<0){
        	perror("Error in read syscall");
        	exit(1);
        }
        
        if(c == '\n'){
        	line_content[line_no][i] = '\0';
        	line_no++;
        	i=0;
        	continue;
        }
        line_content[line_no][i++] = c;
    }


    //close the file
    if(close(fd)<0){	//System Call is used here
    	perror("Error in closing the file");
    	exit(1);
    }
}


void calculate_sum(){
	//Code to split the terms by ','. After this use atoi()
    char * str;
    int k;
    int val;
    int flag = 0;

    for(int j = 1; j < line_no; ++j){
    	k=0;
    	flag=0;
    	str = strtok(line_content[j], ",");
    	while(str!=NULL){
    		if(k == 1){
    			if (strcmp(str, "A")==0)
    			{
    				no_of_studentsA++;
    				flag=1;
    			}
    			else if (strcmp(str, "B")==0)
    			{
    				no_of_studentsB++;
    				flag=2;    			
    			}
    		}
    		else{
    			val = atoi(str);
    			// printf("%d\t", val);
    			if((flag==1) && (k>=2))
    				assignment_totalA[k-1] += val;
    			else if((flag==2) && (k>=2))
    				assignment_totalB[k-1] += val;
    		}
    		str = strtok(NULL, ",");
    		k++;
    		no_of_assignments = k-2;
    	}
    }
}


void* A(){
	for (int i = 1; i <= no_of_assignments; ++i)
	{
		printf("For Section A, average of Assignment %d = %f\n", i, ((float)(assignment_totalA[i]))/no_of_studentsA);
	}
	pthread_exit(NULL);
}

void* B(){
	for (int i = 1; i <= no_of_assignments; ++i)
	{
		printf("For Section B, average of Assignment %d = %f\n", i, ((float)(assignment_totalB[i]))/no_of_studentsB);
	}
	pthread_exit(NULL);
}


int main(int argc, char** argv){

	int status, s;

	read_from_file();
	calculate_sum();

	// printf("%d\n", line_no);

	pthread_t ptid, ptid2;

	
	status = pthread_create(&ptid, NULL, A, NULL);
	if(status){
		perror("Error creating thread");
		return EXIT_FAILURE;
	}
	
	s = pthread_create(&ptid2, NULL, B, NULL);
	if(s){
		perror("Error creating thread");
		return EXIT_FAILURE;
	}

	status = pthread_join(ptid, NULL);
	if(status){
		perror("Error in joining thread");
		return EXIT_FAILURE;
	}
	s = pthread_join(ptid2, NULL);
	if(s){
		perror("Error in joining thread");
		return EXIT_FAILURE;
	}

	printf("\nAverages acrosse Sections: \n");
	for (int i = 1; i <= no_of_assignments; ++i)
	{
		printf("Average of Assignment %d = %f\n", i, ((float)(assignment_totalA[i]+assignment_totalB[i]))/(no_of_studentsA+no_of_studentsB));
	}
	

	return 0;
}
