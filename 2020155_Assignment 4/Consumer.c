#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    char bytes;
    char retval;

    for (int i = 0; i < 8; i++)
    {
        retval = syscall(448, bytes);
        printf("Dequeued byte: %02X\n", retval);
    }
    // syscall(448);
    printf("Return Value: %ld\n", retval);
    
    return 0;
}
