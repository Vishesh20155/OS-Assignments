// First run ./p2Socket and then ./p1Socket

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<time.h>

struct data{
	int id;
	char string[10];
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

int main(int argc, char *argv[]) {

  struct data array[50];
  srand(time(0));

  printf("The 50 random strings generated are: \n");

  for(int i=0; i<50; ++i){
    array[i].id = i;
    randomString(array[i].string);

    printf("%d -- %s\n", array[i].id, array[i].string);
  }

  struct sockaddr_un addr;

  int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    perror("Error in using socket() in P1\n");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, "p1-p2Socket", sizeof(addr.sun_path) - 1);

  if (connect(socket_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
    perror("Error in using connect() in P1\n");
    exit(EXIT_FAILURE);
  }

  int ack=0;

  while(ack<49){
    if(write(socket_fd, array+ack, 5*sizeof(struct data)) < 0){
      perror("Couldn't use write syscall in P1!\n");
      exit(EXIT_FAILURE);
    }
    if(read(socket_fd, &ack, sizeof(int)) < 0){
      perror("Couldn't use read syscall in P1!\n");
      exit(EXIT_FAILURE);
    }
    printf("Acknowledged value: %d\n", ack);
    ack++;
  }

  exit(EXIT_SUCCESS);
}