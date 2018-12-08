#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int cli_sock;
    int ret;

    if (argc != 3) {
        fprintf(stderr, "<%s> <ip> <port>\n", argv[0]);
        return -1;
    }

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr(argv[1]),
        .sin_port = htons(atoi(argv[2])),
    };

    cli_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_sock < 0) {
        return -1;
    }

    ret = connect(cli_sock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        return -1;
    }

    while (1) {
        char msg[] = "sending data to the server";

        send(cli_sock, msg, strlen(msg) + 1, 0);

        sleep(1);
    }

    close(cli_sock);

    return 0;
}
