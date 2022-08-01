#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int i;
    unsigned char bytes[8];
    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, bytes, 8);
    close(fd);
    printf("The bytes read from the /dev/urandom file are: \n");
    for(i = 0; i < 8; ++i)
        printf("%02X\n", bytes[i]);
    printf("\n");
    long retval;

    for (int i = 0; i < 8; i++)
    {
        retval = syscall(449, bytes[i]);
    }
    // syscall(448);
    printf("Return Value: %ld\n", retval);
    
    return 0;
}
