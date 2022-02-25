#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct data{
    int id;
    char string[10];
};

struct msg_struct{
    long type;
    char msg[100];
};


void sendAcknowledgement(char *ack){
    key_t key2 = ftok("P2msgQ.c", 65);
    if(key2 == -1){
        perror("Error in using ftok in P2 for 2nd Queue!\n");
        exit(EXIT_FAILURE);
    }

    int qid2 = msgget(key2, 0666|IPC_CREAT);
    if(qid2==-1)
    {
        perror("Error in generating Message Queue using msgget in P2 for 2nd Queue!\n");
        exit(EXIT_FAILURE);
    }
    struct msg_struct message2;
    message2.type = 1;
    strcpy(message2.msg, ack);

    int ms = msgsnd(qid2, &message2, sizeof(struct data), 0);
    if(ms == -1){
        perror("Error in sending message using msgsnd in P2");
        exit(EXIT_FAILURE);
    }

}


void messageQueue(){
    key_t key = ftok("P1msgQ.c", 57);
    if(key == -1){
        perror("Error in using ftok in P2!\n");
        exit(EXIT_FAILURE);
    }

    int qid = msgget(key, 0666|IPC_CREAT);
    if(qid == -1){
        perror("Error in generating Message Queue using msgget in P2!\n");
        exit(EXIT_FAILURE);
    }

    struct msg_struct message;
    
    int j=0;
    while(j<49)
    {
        printf("Strings passed along with index are:\n");
        for (int i = 0; i < 5; i++)
        {
            if(msgrcv(qid, &message, sizeof(message), 1, 0) == -1) {
                perror("Error in using msgrcv in P2!\n");
                exit(EXIT_FAILURE);
            }   
            printf(" %s\t->\t%.9s\n", message.msg+9, message.msg);
        }
        j = atoi(message.msg+9);
        sendAcknowledgement(message.msg+9);
        j++;
        sleep(1);
    }

    if(msgctl(qid, IPC_RMID, NULL) < 0){
        perror("Error in using msgctl in P2!\n");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char const *argv[])
{
    messageQueue();
    return 0;
}

