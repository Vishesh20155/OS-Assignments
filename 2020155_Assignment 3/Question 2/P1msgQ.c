#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
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


int receiveAcknowledgement(int msgid){
    struct msg_struct message2;
    if(msgrcv(msgid, &message2, sizeof(message2), 1, 0) < 0){
        perror("Error in receiving message in P1!\n");
        exit(EXIT_FAILURE);
    }
    printf("The value acknowledged in P1 is: %s\n", message2.msg);
    
    return atoi(message2.msg);
}


void messageQueue(struct data array[50]){
    key_t key;
    key = ftok("P1msgQ.c", 57);     
    if(key == -1){
        perror("Error in using ftok in P1!\n");
        exit(EXIT_FAILURE);
    }

    int qid = msgget(key, 0666|IPC_CREAT);
    if(qid == -1){
        perror("Error in generating Message Queue using msgget in P1!\n");
        exit(EXIT_FAILURE);
    }

    struct msg_struct message;

    int acknowledgedValue = 0;
    key_t key2 = ftok("P2msgQ.c", 65);
    if(key2 == -1){
        perror("Error in using ftok in P1 for 2nd Queue!\n");
        exit(EXIT_FAILURE);
    }

    int qid2 = msgget(key2, 0666|IPC_CREAT);
    if(qid2==-1)
    {
        perror("Error in generating Message Queue using msgget in P1 for 2nd Queue!\n");
        exit(EXIT_FAILURE);
    }

    while(acknowledgedValue < 49){

        for (int i = 0; i < 5; i++)
        {
            message.type = 1;
            strcpy(message.msg, array[i+acknowledgedValue].string);
            char y[10];
            sprintf(y, "%d", i+acknowledgedValue);
            strcat(message.msg, y);

            if(msgsnd(qid, &message, sizeof(struct data), 0) == -1){
                perror("Error in sending message using msgsnd in P1");
                exit(EXIT_FAILURE);
            }
        }
        acknowledgedValue = receiveAcknowledgement(qid2);
        acknowledgedValue++;
    }

    if(msgctl(qid2, IPC_RMID, NULL) < 0){
        perror("Error in using msgctl for 2nd Message Queue\n");
        exit(EXIT_FAILURE);
    }


}


int main(int argc, char const *argv[])
{
    struct data array[50];
    srand(time(0));

    printf("The randomly generated 50 strings are:\n");

    for(int i=0; i<50; ++i){
            array[i].id = i;
            randomString(array[i].string);

            printf("%d -- %s\n", array[i].id, array[i].string);
    }

    messageQueue(array);
    return 0;
}
