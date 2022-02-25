#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

sem_t bowl;
int philosopher_numbers[5] = {0, 1, 2, 3, 4};


void *attempt_to_eat(void *arg){
    
    /* add printf lines for forks and change variable names*/

    int index = *(int*)arg;
    while(1){
        sem_wait(&bowl);
		int semVal;
		sem_getvalue(&bowl, &semVal);
		printf("Philosopher %d takes bowl %d\n", index, semVal);
        printf("Philosopher %d is eating with fork %d\n\n", index, index);
        sem_post(&bowl);
		printf("Philosopher %d puts back bowl %d\n\n", index, semVal);
        sleep(1);
    }

}

int main()
{

	int i;
	pthread_t thread_id[5];

	sem_init(&bowl, 0, 4);

	for (i = 0; i < 5; i++) {
		pthread_create(&thread_id[i], NULL, attempt_to_eat, &philosopher_numbers[i]);
	}

	for (i = 0; i < 5; i++)

		pthread_join(thread_id[i], NULL);
}