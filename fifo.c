#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int ret;

    if (argc != 2) {
        fprintf(stderr, "<%s> create/open\n", argv[0]);
        return -1;
    }

    int fd;

    if (!strcmp(argv[1], "create")) {
        unlink("/fifo_test");

        ret = mkfifo("/fifo_test", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (ret < 0) {
            return -1;
        }

        fd = open("/fifo_test", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
        if (fd < 0) {
            return -1;
        }

        while (1) {
            char *sender_msg = "Hello from sender";
            write(fd, sender_msg, strlen(sender_msg) + 1);

            sleep(1);
        }
    } else if (!strcmp(argv[1], "open")) {
        fd = open("/fifo_test", O_RDWR);
        if (fd < 0) {
            return -1;
        }

        while (1) {
            char rxmsg[200];

            ret = read(fd, rxmsg, sizeof(rxmsg));
            if (ret <= 0) {
                break;
            }

            printf("msg fromsender: %s\n", rxmsg);
        }
    }

    return 0;
}

