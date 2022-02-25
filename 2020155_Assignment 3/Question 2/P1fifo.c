#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>


struct data{
        int id;
        char string[10];
};

int receiveAcknowledgement(int fd){
    int ack;
    if(read(fd, &ack, sizeof(int)) < 0){
            perror("Error in writing to fifo in P2!\n");
            exit(EXIT_FAILURE);
    }

    printf("Acknowledgement received with index: %d\n", ack);
    return ack;
}

void randomString(char str[10]){
    int k;
    char chars[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    strcpy(str, "");
    for (int i = 0; i < 9; i++)
    {
        k = rand()%strlen(chars);
        str[i] = chars[k];
    }
    str[9] = '\0';

}

int main(int argc, char *argv[]){

    char fifoName[25] = "P1-P2Fifo";
    char fifoName2[25] = "P2-P1Fifo";
    // printf("%s\n", fifoName);

    printf("The 50 random strings generated are: \n");

    struct data array[50];
    srand(time(0));

    for(int i=0; i<50; ++i){
        array[i].id = i;
        randomString(array[i].string);

        printf("%d -- %s\n", array[i].id, array[i].string);
    }

    if(mkfifo(fifoName, 0777)<0){
        perror("Error in using mkfifo in P1!\n");
        exit(EXIT_FAILURE);
    }

    if(mkfifo(fifoName2, 0777)<0){
        perror("Error in using mkfifo in P1 for 2nd time!\n");
        exit(EXIT_FAILURE);
    }

    int fifo_fd = open(fifoName, O_WRONLY);
    if(fifo_fd<0){
        perror("Error in opening fifo in P1!\n");
        exit(EXIT_FAILURE);
    }

    int fifo_fd2 = open(fifoName2, O_RDONLY);
    if(fifo_fd2<0){
        perror("Error in opening fifo for reading in P1!\n");
        exit(EXIT_FAILURE);
    }

    int acknowledgedValue=0;

    while (acknowledgedValue<49)
    {
        if(write(fifo_fd, array+acknowledgedValue, 5*sizeof(struct data)) < 0){
            perror("Error in writing to fifo in P1!\n");
            exit(EXIT_FAILURE);
        }
        if(read(fifo_fd2, &acknowledgedValue, sizeof(int)) < 0){
            perror("Error in reading from fifo in P1!\n");
            exit(EXIT_FAILURE);
        }
        printf("Acknowledgement received with index: %d\n", acknowledgedValue);
        acknowledgedValue++;
    }

    if(close(fifo_fd2) < 0){
            perror("Error in closing the fifo for reading in P1!\n");
            exit(EXIT_FAILURE);
    }

    if(close(fifo_fd) < 0){
            perror("Error in closing the fifo in P1!\n");
            exit(EXIT_FAILURE);
    }

    if(remove(fifoName) < 0){
            perror("Error in removing the fifo in P1!\n");
            exit(EXIT_FAILURE);
    }

    return 0;
}