#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int ret;
    struct stat s;

    if (argc != 2) {
        printf("%s [file name]\n", argv[0]);
        return -1;
    }

    ret = stat(argv[1], &s);
    if (ret) {
        printf("failed to stat: %s\n", strerror(errno));
        return -1;
    }

    printf("file %s size %ld\n", argv[1], s.st_size);
    return 0;
}
