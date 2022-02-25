#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<stdlib.h>

struct data{
	int id;
	char string[10];
};

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;

  int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

  if (socket_fd == -1) {
    perror("Error in using socket in P2!\n");
    exit(EXIT_FAILURE);
  }

  if (remove("p1-p2Socket") == -1 && errno != ENOENT) {
    perror("Error in removing the socket in P2!\n");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, "p1-p2Socket", sizeof(addr.sun_path) - 1);

  if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) < 0) {
    perror("Error in binding the socket in P2!\n");
    exit(EXIT_FAILURE);
  }

  if (listen(socket_fd, 5) == -1) {
    perror("Error in listen in P2!\n");
    exit(EXIT_FAILURE);
  }

  printf("Connection Awaited...\n");
  int client_fd = accept(socket_fd, NULL, NULL);

  struct data d[5];

  while(1){
    printf("The strings along with their IDs received from P1 are:\n");
    read(client_fd, d, 5*sizeof(struct data));
    for(int i=0;i<5;++i){
      printf("%d\t->\t%s\n", d[i].id, d[i].string);
    }
    write(client_fd, &(d[4].id), sizeof(int));
    if(d[4].id == 49)
      break;
  }

  if (close(client_fd) == -1) {
    perror("Error in using close in P2\n");
  }
  
}