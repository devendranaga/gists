#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;

    if (argc != 2) {
        fprintf(stderr, "<%s> filename\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("");
        return -1;
    }

    while (1) {
        char bytes[1000];
        int ret;

        fprintf(stderr, "enter something to send to the file %s\n", argv[1]);

        ret = read(1, bytes, sizeof(bytes));
        if (ret <= 0) {
            break;
        }

        if (bytes[0] == '\n') {
            break;
        }

        write(fd, bytes, ret);
    }

    close(fd);

    return 0;
}

