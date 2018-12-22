#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    int ret;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return -1;
    }

    struct sockaddr_in addr;

    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);

    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        fprintf(stderr, "failed to bind : %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    while (1) {
        char buf[100];

        ret = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        if (ret < 0) {
            break;
        }
    }

    close(fd);

}

