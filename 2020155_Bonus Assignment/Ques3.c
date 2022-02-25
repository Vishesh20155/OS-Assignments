#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

sem_t forks[5];
sem_t bowl;

int philosopher_numbers[5] = {0,1,2,3,4};
int canEat[5] = {1,1,1,1,1};

void updateWhoCanEat(int x){
	for(int i=0; i<5; ++i){
		if(i==x){
			canEat[i]=0;
		}
		else{
			canEat[i]=1;
		}
	}
}

void* Attempt_to_eat(void* args){
	int index = *(int*) args;

	while(1)
	{
		if(canEat[index]){
		if(index != 4){
			// sem_wait(&turn);
			sem_wait(&forks[index]);
			sem_wait(&forks[(index + 4)%5]);
			printf("Philosopher %d picks up fork %d and %d\n", index, index, (index+4)%5);
            sem_wait(&bowl);
            int semVal;
            sem_getvalue(&bowl, &semVal);
            printf("Philosopher %d takes bowl %d\n", index, semVal);

			printf("\nPhilosopher %d is eating\n\n", index);
			updateWhoCanEat(index);
			// sem_post(&turn);
			sleep(1);

			// sem_wait(&turn);
			sem_post(&forks[index]);
			sem_post(&forks[(index + 4)%5]);
            sem_post(&bowl);
			printf("Philosopher %d leaves fork %d and %d and bowl\n", index, index, (index+4)%5);
            
			// sem_post(&turn);

		}
		else{
			// sem_wait(&turn);
			sem_wait(&forks[(index + 4)%5]);
			sem_wait(&forks[index]);
			printf("Philosopher %d picks up fork %d and %d\n", index, (index+4)%5, index);
            sem_wait(&bowl);
            int semVal;
            sem_getvalue(&bowl, &semVal);
            printf("Philosopher %d takes bowl %d\n", index, semVal);

			printf("\nPhilosopher %d is eating\n\n", index);
			updateWhoCanEat(index);
			// sem_post(&turn);
			sleep(1);

			// sem_wait(&turn);
			sem_post(&forks[(index + 4)%5]);
			sem_post(&forks[index]);
            sem_post(&bowl);
			printf("Philosopher %d leaves fork %d and %d and bowl\n", index, (index+4)%5, index);
			// sem_post(&turn);
		}
	}}
}

int main(int argc, char const *argv[])
{
	pthread_t philosopher[5];
	int philosopher_num;

	for(int i=0;i<5;++i){
		sem_init(&forks[i], 0, 1);
	}

    sem_init(&bowl, 0, 4);

	for(int i=0; i<5; ++i){
		pthread_create(&philosopher[i], NULL, Attempt_to_eat, &philosopher_numbers[i]);
	}

	for(int i=0; i<5; ++i){
		pthread_join(philosopher[i], NULL);
	}

	return 0;
}
