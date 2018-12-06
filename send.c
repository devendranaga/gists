#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SAMPLE_SERVER_CONN 10

int main(int argc, char **argv)
{
    int ret;
    int sock;
    struct sockaddr_in remote;
    socklen_t remote_len;
    char buf[1000];

    if (argc != 3) {
        fprintf(stderr, "%s [ip] [port]\n", argv[0]);
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("failed to socket\n");
        return -1;
    }

    remote.sin_family = AF_INET;
    remote.sin_addr.s_addr = inet_addr(argv[1]);
    remote.sin_port = htons(atoi(argv[2]));

    remote_len = sizeof(struct sockaddr_in);

    ret = connect(sock, (struct sockaddr *)&remote, remote_len);
    if (ret < 0) {
        perror("failed to accept\n");
        close(sock);
        return -1;
    }

    printf("connect success %d\n", ret);

    printf("enter something to send\n");

    fgets(buf, sizeof(buf), stdin);

    ret = send(sock, buf, strlen(buf), 0);
    if (ret < 0) {
        printf("failed to send %s\n", buf);
        close(sock);
        return -1;
    }

    printf("sent %d bytes\n", ret);

    close(sock);

    return 0;
}
