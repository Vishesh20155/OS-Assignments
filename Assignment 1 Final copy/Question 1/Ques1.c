#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<string.h>
#include<sys/wait.h>


void read_from_file(char line_content[][500], int *line_no){
	int fd = open("student_record.csv", O_RDONLY); //System Call used
	//student_record.csv should be in same directory

	if (fd<0)
    {
        printf("Error Number % d\n", errno);
        perror("Program");  
        exit(1);              
    }

    char c;
    int size = 1;
    (*line_no)=0;
    int i=0;
    while(size>0){
        size = read(fd, &c, 1);	//System call used
        if(size<0){
        	perror("Error in read syscall");
        	exit(1);
        }
        
        if(c == '\n'){
        	line_content[*line_no][i] = '\0';
        	(*line_no)++;
        	i=0;
        	continue;
        }
        line_content[*line_no][i++] = c;
    }


    //close the file
    if(close(fd)<0){	//System Call is used here
    	perror("Error in closing the file");
    	exit(1);
    }
}

int assignment_total[100];

void calculate_sum(char line_content[][500], char section[], int line_no, int *no_of_assignments, int *no_of_students){
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
    		if((k == 1) && (strcmp(str, section)==0)){
    			flag=1;
    			(*no_of_students)++;
    		}
    		else{
    			val = atoi(str);
    			// printf("%d\t", val);
    			if((flag==1) && (k>=2))
    				assignment_total[k-1] += val;
    		}
    		str = strtok(NULL, ",");
    		k++;
    		(*no_of_assignments) = k-2;
    	}
    }
}

void print_ass(int no_of_assignments, int no_of_students, char section[]){
	if(write(1, "For Section ", strlen("For Section ")) < 0){
		perror("Error in write syscall");
		exit(1);
	}
	if(write(1, section, strlen(section)) < 0){
		perror("Error in write syscall");
		exit(1);
	}
	if(write(1, ":\n", 2) < 0){
		perror("Error in write syscall");
		exit(1);
	}
	
	for (int i = 1; i <= no_of_assignments; ++i)
	{
		printf("Average of Assignment %d = %f\n", i, ((float)(assignment_total[i]))/no_of_students);
	}
}

int main(int argc, char const *argv[])
{
	// for (int j = 0; j < line_no; ++j)
 //    {
 //    	printf("%s\n", line_content[j]);
 //    }

	int status;
	pid_t p = fork();	//System Call p=-1 for fail
	if(p==-1){
		perror("Error while using fork.");
		exit(1);
	}
	int line_no;
	int no_of_assignments=0;
	int no_of_students=0;

	if(p==0){
		char line_content[500][500];
		read_from_file(line_content, &line_no);
	    calculate_sum(line_content, "A", line_no, &no_of_assignments, &no_of_students);
	    print_ass(no_of_assignments, no_of_students, "A");
	    printf("\n");
	    exit(EXIT_SUCCESS);	//System Call is used
	}

	else{
		if(waitpid(p, &status, 0) < 0)	//System call is used 
		{
			perror("wait");
			return EXIT_FAILURE;
		}
		if (WIFEXITED(status)){
			char line_content[5000][500];
			read_from_file(line_content, &line_no);
		    calculate_sum(line_content, "B", line_no, &no_of_assignments, &no_of_students);
		    print_ass(no_of_assignments, no_of_students, "B");
		    printf("\n");
		}
	}

	return 0;
}