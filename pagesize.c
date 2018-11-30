#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("sysconf(pagesize) %ld\n", sysconf(_SC_PAGESIZE));
}

