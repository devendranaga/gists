#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    int stdout_fd;

    if (argc != 2) {
        fprintf(stderr, "<%s> text\n", argv[0]);
        return -1;
    }

    stdout_fd = fcntl(1, F_DUPFD, 3);
    if (stdout_fd < 0) {
        fprintf(stderr, "failed to fcntl dupfd %s\n", strerror(errno));
        return -1;
    }

    write(stdout_fd, argv[1], strlen(argv[1]) + 1);

    return 0;
}

