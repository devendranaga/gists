#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    int ret;

    if (argc != 2) {
        fprintf(stderr, "<%s> filename\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return -1;
    }

    ret = fchmod(fd, 0777);
    if (ret < 0) {
        fprintf(stderr, "fchmod failure %s\n", strerror(errno));
    } else {
        fprintf(stderr, "succesfully set permissions of file %s\n", argv[1]);
    }

    close(fd);

    // perform stat() to verify
    struct stat s_;

    ret = stat(argv[1], &s_);
    if (ret < 0) {
        fprintf(stderr, "failed to stat %s\n", argv[1]);
        return -1;
    }

    fprintf(stderr, "file permissions %o\n", s_.st_mode);

    return 0;
}

