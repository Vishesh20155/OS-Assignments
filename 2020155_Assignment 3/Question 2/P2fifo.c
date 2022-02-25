#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

struct data{
        int id;
        char string[10];
};

void printBuffer(struct data buf[5]){
    for (int i = 0; i < 5; i++)
    {
        printf("%d\t->\t%s\n", buf[i].id, buf[i].string);
    }
    
}

void sendAcknowledgement(struct data buf, int fd){
    if(write(fd, &buf.id, sizeof(int)) < 0){
            perror("Error in writing to fifo in P2!\n");
            exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){

    char fifoName[25] = "P1-P2Fifo";
    char fifoName2[25] = "P2-P1Fifo";
    //printf("%s\n", fifoName);

    int fifo_fd = open(fifoName, O_RDONLY);
    if(fifo_fd<0){
        perror("Error in opening fifo for reading in P2!\n");
        exit(EXIT_FAILURE);
    }


    int fifo_fd2 = open(fifoName2, O_WRONLY);
    if(fifo_fd2<0){
        perror("Error in opening fifo for writing in P2!\n");
        exit(EXIT_FAILURE);
    }

    struct data buffer[5];

    while(1)
    {
        printf("The strings along with their IDs received in this batch are:\n");

        if(read(fifo_fd, buffer, 5*sizeof(struct data)) < 0){
                perror("Error in reading from fifo in P2!\n");
                exit(EXIT_FAILURE);
        }
        printBuffer(buffer);

        sendAcknowledgement(buffer[4], fifo_fd2);
        if(buffer[4].id >= 49)
            break;
    }

    if(close(fifo_fd) < 0){
            perror("Error in closing the fifo for reading in P2!\n");
            exit(EXIT_FAILURE);
    }

    if(close(fifo_fd2) < 0){
            perror("Error in closing the fifo for writing in P2!\n");
            exit(EXIT_FAILURE);
    }

    if(remove(fifoName2) < 0){
            perror("Error in removing the fifo in P2!\n");
            exit(EXIT_FAILURE);
    }

    return 0;
}
