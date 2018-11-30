#include <stdio.h>
#include <unistd.h>

int main()
{
    long iov = sysconf(_SC_IOV_MAX);

    printf("max sysconf iov %ld\n", iov);

    return 0;
}

