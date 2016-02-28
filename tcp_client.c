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

#define TCP_SERVER_PORT 21111

int main()
{
    int cli_sock;
    int ret;

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(TCP_SERVER_PORT),
    };

    cli_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (cli_sock < 0) {
        return -1;
    }

    ret = connect(cli_sock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        return -1;
    }

    char msg[] = "sending data to the server";

    send(cli_sock, msg, strlen(msg) + 1, 0);

    close(cli_sock);

    return 0;
}
