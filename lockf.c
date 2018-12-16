#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

off_t filesize(char *file)
{
    struct stat s;
    int ret;

    ret = stat(file, &s);
    if (ret < 0) {
        return -1;
    }

    return s.st_size;
}

int main(int argc, char **argv)
{
    pid_t pid;
    int fd;
    off_t size;
    int ret;

    if (argc != 2) {
        fprintf(stderr, "<%s> filename\n", argv[0]);
        return -1;
    }

    size = filesize(argv[1]);

    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return -1;
    }

    pid = fork();
    if (pid == 0) {
        ret = lockf(fd, F_LOCK, size);
        if (ret < 0) {
            printf("cannot lock.. %s\n", strerror(errno));
            return -1;
        }

        printf("lock acquired.. now set to sleep\n");
        sleep(4);
        printf("unlock..\n");

        ret = lockf(fd, F_ULOCK, size);
    } else {
        sleep(1);
        ret = lockf(fd, F_LOCK, size);
        if (ret < 0) {
            printf("cannto loock.. %s\n", strerror(errno));
            return -1;
        }

        printf("lock acquired by parent..\n");
        lockf(fd, F_ULOCK, size);
    }

    return 0;
}

