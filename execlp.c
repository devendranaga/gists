#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int ret;
    pid_t pid;

    if (argc != 3) {
        fprintf(stderr, "<%s> command command-opt ..\n", argv[0]);
        return -1;
    }

    pid = fork();
    if (pid != 0) {
        ret = execlp(argv[1], argv[1], argv[2], NULL);
        if (ret < 0) {
            fprintf(stderr, "failed to execl %s\n", strerror(errno));
            return -1;
        }
    }
}

