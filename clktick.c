#include <stdio.h>
#include <unistd.h>

int main()
{
    int clock_tick;

    clock_tick = sysconf(_SC_CLK_TCK);
    printf("clock ticks %d\n", clock_tick);

    return 0;
}

