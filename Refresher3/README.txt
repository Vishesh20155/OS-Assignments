The following are the descriptions of the programs in this file:


Q1Calendar.sh:
For Question 1
In this program, a bash script is made for Question 1 in which we had to print the calendar for the entire month.

In order to run this program:
1. First go to the directory in which the program is stored and give executible permission for the bash script using the command: chmod +x Q1Calendar.sh.

2. Next write the command along with command line inputs: ./Q1Calendar.sh (date in dd-mm-yyyy format)
Eg: ./Q1Calendar.sh 12-09-2021 --> prints the calendar of September 2021

The program also checks whether the date is valid or not.


Q2Calculator.sh:
For Question 2
In this program, a bash script is made for Question 2 in which we had to code a calculator whose operator and operands were provided by the user.
The program takes in command line input and the number of operands is variable but must be greater than 2.

In order to run this program:

1. First go to the directory in which the program is stored and give executible permission for the bash script using the command: chmod +x Q2Calculator.sh.

2. Next write the command along with command line inputs: ./Q2Calculator.sh (operator list of operands)
Eg: ./Q2Calculator.sh add 5 6 4 --> prints the sum 5+6+7.

Each of the operator(add, sub, mul, div, exp) take in any number of operands and perform the (integral)computation left to right.


For all the C programs, executible file of the programs will be made by running the make command. Then you can run any of the files to run program.


Q3BST.c:

In this C program, implementation of BST in C is performed. The program performs basic BST operations such as insertion of element, deletion of an element or printing the inorder traversal of BST.

The program is a menu driven program from which one can insert and delete as many elements by choosing options 1 and 2 respectively. One can also print the inorder traversal of the array by entering option 3. If one chooses any other option apart from 1, 2 or 3 the program terminates

To run this program, just double click on the executible file BST formed after running the make command or use the command ./BST or gcc Q3BST.c to compile and run the program.



Q3AVL.c:

In this C program, implementation of AVL Tree in C is performed. The program performs basic AVL Tree operations such as insertion of element, deletion of an element or printing the inorder traversal of AVL Tree.

The program is a menu driven program from which one can insert and delete as many elements by choosing options 1 and 2 respectively. One can also print the inorder traversal of the array by entering option 3. If one chooses any other option apart from 1, 2 or 3 the program terminates

To run this program, just double click on the executible file AVL formed after running the make command or use the command ./AVL or gcc Q3AVL.c to compile and run the program.


Q4Sort.c:
For Question 4
In this C program, implementation of Bubble Sort and Selection Sort in C is performed.

First, the program will ask the number of elements you wish to enter in the array. Next it will ask for the array elements. Then you will have to choose either 1 or 2 for using bubble sort or selection sort.

To run this program, just double click on the executible file AVL formed after running the make command or use the command ./Sort (or gcc Q4Sort.c) to compile and run the program(./a.out).


Q4SortCommandLineInput.c:
For Question 4
This program is logically same as above program. The difference is that it takes the input as command line arguments.

To sort the array using bubble sort write the command (after running make command): 
./Sort_CommandLineInput bubble (list of numbers to be sorted)

To sort the array using selection sort write the command (after running make command): 
./Sort_CommandLineInput selection (space separated list of numbers to be sorted)

Eg: ./Sort_CommandLineInput selection 5 4 3 2 1