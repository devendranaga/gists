#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

struct bin_data {
    int a;
    double b;
} __attribute__ ((__packed__));

int main(int argc, char **argv)
{
    int fd;

    if (argc != 2) {
        fprintf(stderr, "<%s> filename\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        fprintf(stderr, "failed to open %s\n", strerror(errno));
        return -1;
    }

    struct bin_data b[10];
    int i;

    for (i = 0; i < 10; i ++) {
        b[i].a  = i;
        b[i].b = i + 4.4;
    };

    write(fd, b, sizeof(b));

    close(fd);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "failed to open file %s\n", strerror(errno));
        return -1;
    }

    struct bin_data d[10];

    read(fd, d, sizeof(d));

    for (i = 0; i < 10; i ++) {
        fprintf(stderr, "a %d b %f\n", d[i].a, d[i].b);
    }

    close(fd);

    return 0;
}

