For the evaluation of this Assignment, after adding the extracted file to the VM, run the make command in the directory.

After that, 3 executible files would be created.

Run ./Q1 for testing the code for Part 1	- Ques.c file
Run ./Q2 for testing the code for Part 2	- Ques2.c file
Run ./Q3 for testing the code for Part 3	- Ques3.c file

Synchronisation Primitives Used(in all three parts):
	SEMAPHORES: 
	Both counting and binary semaphores are used.
	In the counting semaphores, a semaphore is made whose initial value represents the number of resources that are available for all the processes to use. In binary semaphore, there is only one resource that is available for the use of the threads. So, in our case, each of the fork is represented by a binary semaphore as one fork can only be taken by one philosopher at a time. The bowls are accessible to all the philosophers so it is represented as a counting semaphore with initial value 4.
	The semaphores are initialised using the sem_init functions. To use a semaphore, sem_wait is used. This ensures that if value of the semaphore is >= 0, then we can use that resource else not and the process is sent to the waiting state. Also the wait decrements the value of the semaphore.
	After using the resource, we call the sem_post function that ensures an increment of the value of the semaphore os that other processes in waiting state, waiting for the resource to free up for their use can use it.


The part 1 of the question is the normal Dining Philosopher's problem. It has been ensured that there is no deadlock using an array of binary semaphores. The fork on the left of the philosopher 'i' is fork 'i'. So all the philosophers, except the philosopher at index 4 (0 - based indexing) first pick up the fork on their left and then on their right if it is available. The solution to avoid deadlock is that the 5th philosopher i.e. with index '4' does the opposite i.e. it first picks up the fork on his right and then the fork on his left. This ensures that there is not a case wherein all the philosophers have a single fork in their hand and all are waiting for each other to obtain the second fork.


In part 2, since each philosopher requires just one fork to eat, it is assumed in our solution that philosopher i picks up fork i always to eat(since fairness is not required). So in this we just use one counting semaphore for the bowls. The deadlock is avoided as even if 4 philosophers have 4 bowls, then they can easily acquire their respective forks and then leave one of the bowls for the other to eat.


In part 3, a combination of the above 2 parts has been coded, there is an array of binary semaphores for using forks and a counting semaphore for the bowls. Also the bowl can only be accessed when the philosopher has taken 2 forks. Since at the max, that too hypothetically(accounting for the worst case), 3 philosophers can have 2 forks each, this approach of taking the fork after acquiring 2 forks would never result in a deadlock.