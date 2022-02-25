#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
	char name[50], yearOfJoining[50], program[50];
	int rollno;
	struct student *nxt;
};

struct student *head = NULL;
struct student *tail = NULL;

void printMenu(){
	printf("MENU:\n");
	printf("1. Insert an element in Linked List.\n");
	printf("2. Delete an element from Linked List.\n");
	printf("3. Print the Linked List.\n");
	printf("Any other number to terminate the program.\n");
}

void printLL(struct student *t){
	printf("\n");
	if(t == NULL)
		printf("Linked List is empty\n");

		while(t != NULL){
		printf("\nNAME: %s\tR.No.: %d\tJOINING YR: %s\tPROGRAM: %s", t->name, t->rollno, t->yearOfJoining, t->program);
		t = t->nxt;
	}
}

void insert(){
	// char n[50], yearOfJoining, program;
	struct student *temp = (struct student*)(malloc (sizeof(struct student)));
	printf("\nEnter the name of the student: ");
	scanf("%s", temp->name);
	// char str[100] = "hi";
 //    scanf("%[^\n]s",str);
 //    strcpy(temp->name, str);
	// This method to take spaces in between was not working on my machine in this particular program. However, if I used it in some other program it worked well
	printf("Enter the roll number of the student in integer format: ");
	scanf("%d", &temp->rollno);
	printf("Enter the year of joining of the student: ");
	scanf("%s", temp->yearOfJoining);	
	printf("Enter the program in which the student is enrolled: ");
	scanf("%s", temp->program);
	temp->nxt = NULL;

	if(head == NULL){
		head = temp;
		tail = temp;
		return;
	}
	tail->nxt = temp;
	tail = temp;
}

void delete(){
	int r;
	printf("\nEnter the rollno of the student whose record you wish to delete: ");
	scanf("%d", &r);
	struct student *temp = head;
	struct student *t = NULL;
	while(temp!=NULL){
		if(temp->rollno == r){
			if (head == tail)
			{
				head = tail = NULL;
				free(temp);
				printf("Element deleted");
				return;
			}
			if(temp == tail)
				tail = t;
			if(t == NULL)
				head = temp->nxt;
			else
				t->nxt = temp->nxt;
			temp->nxt = NULL;
			free(temp);
			printf("Element deleted");
			return;
		}
		t = temp;
		temp = temp->nxt;
	}
	printf("\nStudent not found");
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
			insert();
			printf("\nElement inserted.\n");
		}
		else if(opt == 2){
			delete();
		}
		else if(opt == 3){
			printLL(head);
			printf("\n");
		}
		else{
			exit(0);
		}
	}
	return 0;
}
