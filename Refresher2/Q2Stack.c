#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
	char name[50], yearOfJoining[50], program[50];
	int rollno;
	struct student *nxt;
};

struct student *top = NULL;

void printMenu(){
	printf("MENU:\n");
	printf("1. Push.\n");
	printf("2. Pop.\n");
	printf("3. View Top Element.\n");
	printf("Any other number to terminate the program.\n");
}

void viewTop(){
	printf("\n");
	if(top == NULL)
		printf("Empty Stack!\n");

	else{
		printf("\nNAME: %s\tR.No.: %d\tJOINING YR: %s\tPROGRAM: %s", top->name, top->rollno, top->yearOfJoining, top->program);
	}
}

void push(){
	// char n[50], yearOfJoining, program;
	struct student *temp = (struct student*)(malloc (sizeof(struct student)));
	if(temp == NULL){
		printf("\nHeap Overflow!\n");
		return;
	}
	printf("\nEnter the name of the student: ");
	scanf("%s", temp->name);
	// char str[100] = "hi";
 //    scanf("%[^\n]s",str);
 //    strcpy(temp->name, str);


	/* This method to take spaces in between was not working on my machine in this particular program. However, if I used it in some other program it worked well*/
	

	printf("Enter the roll number of the student in integer format: ");
	scanf("%d", &temp->rollno);
	printf("Enter the year of joining of the student: ");
	scanf("%s", temp->yearOfJoining);	
	printf("Enter the program in which the student is enrolled: ");
	scanf("%s", temp->program);
	temp->nxt = top;

	top = temp;
}

int pop(){
	if(top == NULL){
		return -1;
	}
	else{
		int x = top->rollno;
		struct student *temp = top;
		top = top->nxt;
		temp->nxt = NULL;
		free(temp);
		return x;
	}
}

int main(int argc, char const *argv[])
{
	int opt;
	char ch = 'y';

	printMenu();
	while(1){
		printf("\nChoose an option: ");
		scanf("%d", &opt);
		if(opt == 1){
			push();
			printf("\nElement pushed.\n");
		}
		else if(opt == 2){
			int x = pop();
			if(x == -1){
				printf("Stack Empty!\n");
			}
			else{
				printf("Student with roll number: %d popped.\n", x);
			}

		}
		else if(opt == 3){
			viewTop();
			printf("\n");
		}
		else{
			exit(0);
		}
	}
	return 0;
}
