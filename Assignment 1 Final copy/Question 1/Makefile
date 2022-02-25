all: Q1Fork Q1Thread

Q1Fork: Ques1.c
	gcc -S Ques1.c
	gcc -c Ques1.s
	gcc Ques1.o -o Q1Fork

Q1Thread: Ques1_Threads.c
	gcc -S -pthread Ques1_Threads.c 
	gcc -c -pthread Ques1_Threads.s 
	gcc -pthread Ques1_Threads.o -o Q1Thread 