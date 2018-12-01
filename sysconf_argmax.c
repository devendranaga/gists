#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("sysconf(_SC_ARG_MAX) %ld\n", sysconf(_SC_ARG_MAX));
}

