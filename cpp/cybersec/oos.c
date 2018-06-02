#include <stdio.h>

int *ptr;

void getPtr()
{
    int val = 10;

    ptr = &val;
}

int main()
{
    getPtr();

    printf("ptr value is %d\n", *ptr);
}
