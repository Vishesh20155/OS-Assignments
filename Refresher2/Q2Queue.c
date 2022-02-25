#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
	char name[50], yearOfJoining[50], program[50];
	int rollno;
	struct student *nxt;
};

struct student *front = NULL;
struct student *rear = NULL;

void printMenu(){
	printf("MENU:\n");
	printf("1. Enque.\n");
	printf("2. Deque.\n");
	printf("3. Peek - View the element at front.\n");
	printf("Any other number to terminate the program.\n");
}

void peek(){
	printf("\n");
	if(front == NULL)
		printf("Empty Queue!\n");

	else{
		printf("\nNAME: %s\tR.No.: %d\tJOINING YR: %s\tPROGRAM: %s", front->name, front->rollno, front->yearOfJoining, front->program);
	}
}

void enque(){
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
	temp->nxt = NULL;
	if(rear == NULL){
		front = rear = temp;
		return;
	}
	rear->nxt = temp;
	rear = temp;
}

int deque(){
	if(front == NULL){
		return -1;
	}
	else{
		int x = front->rollno;
		struct student *temp = front;
		front = front->nxt;
		if(front == NULL){
			rear = NULL;
		}
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
			enque();
			printf("\nElement inserted in Queue.\n");
		}
		else if(opt == 2){
			int x = deque();
			if(x == -1){
				printf("Queue Empty!\n");
			}
			else{
				printf("Student with roll number: %d removed from Queue.\n", x);
			}

		}
		else if(opt == 3){
			peek();
			printf("\n");
		}
		else{
			exit(0);
		}
	}
	return 0;
}
