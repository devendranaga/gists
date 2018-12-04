#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int i = 0;
    char var[20];
    int ret;

    if (argc != 3) {
        fprintf(stderr, "<%s> var val\n", argv[0]);
        return -1;
    }

    ret = setenv(argv[1], argv[2], 1);
    if (ret < 0) {
        return -1;
    }

    printf("Set %s\n", argv[2]);


    printf("get %s=%s\n", argv[1], getenv(argv[1]));

    return 0;
}

