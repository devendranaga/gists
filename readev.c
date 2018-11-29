#include <stdio.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd;
    struct iovec iov[4];

    if (argc != 2) {
        fprintf(stderr, "<%s> filename\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "failed to open file %s\n", argv[1]);
        return -1;
    }

    int i;

    for (i = 0; i < 4; i ++) {
        iov[i].iov_base = calloc(1, 1024);
        if (!iov[i].iov_base) {
            return -1;
        }

        iov[i].iov_len = 1024;
    }

    int ret;

    ret = readv(fd, iov, 4);
    if (ret <= 0) {
        fprintf(stderr, "failed to read from file\n");
    }

    int bytes = 0;

    if (ret < 4 * 1024) {
        fprintf(stderr, "read [%d] expected 4096 \n", ret);
    }

    for (i = 0; i < 4; i ++) {
        if (bytes < ret) {
            char *content = iov[i].iov_base;

            fprintf(stderr, "---- iov[%d]: size [%ld]-------\n", i, iov[i].iov_len);
            fprintf(stderr, "%s", content);

            free(content);

            bytes += iov[i].iov_len;
        }
    }

    close(fd);

    return 0;
}

