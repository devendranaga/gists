#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TCP_SERVER_PORT 21111

int main(int argc, char **argv)
{
    int ret;
    fd_set rdset;
    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(TCP_SERVER_PORT),
    };

    int max_fd = 0;
    int set_reuse = 1;
    int serv_sock;

    int client_list[100];
    int i;

    for (i = 0; i < sizeof(client_list) / sizeof(client_list[0]); i ++) {
        client_list[i] = -1;
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0) {
        return -1;
    }

    ret = setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &set_reuse, sizeof(set_reuse));
    if (ret < 0) {
        return -1;
    }

    ret = bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        return -1;
    }

    ret = listen(serv_sock, 100);
    if (ret < 0) {
        return -1;
    }

    if (max_fd < serv_sock)
        max_fd = serv_sock;

    FD_ZERO(&rdset);

    FD_SET(serv_sock, &rdset);

    while (1) {
        int clifd;
        fd_set allset = rdset;

        ret = select(max_fd + 1, &allset, 0, 0, NULL);
        if (ret > 0) {
            if (FD_ISSET(serv_sock, &allset)) {
                clifd = accept(serv_sock, NULL, NULL);
                if (clifd < 0) {
                    continue;
                }

                for (i = 0; i < sizeof(client_list) / sizeof(client_list[0]); i ++) {
                    if (client_list[i] == -1) {
                        client_list[i] = clifd;
                        FD_SET(clifd, &rdset);
                        if (max_fd < clifd)
                            max_fd = clifd;
                        printf("new fd %d\n", clifd);
                        break;
                    }
                }
            } else {
                for (i = 0; i < sizeof(client_list) / sizeof(client_list[0]); i ++) {
                    if ((client_list[i] != -1) &&
                        (FD_ISSET(client_list[i], &allset))) {
                        char buf[100];

                        printf("client %d\n", client_list[i]);
                        ret = recv(client_list[i], buf, sizeof(buf), 0);
                        if (ret <= 0) {
                            printf("closing %d\n", client_list[i]);
                            FD_CLR(client_list[i], &rdset);
                            close(client_list[i]);
                            client_list[i] = -1;
                            continue;
                        }

                        printf("read %s\n", buf);
                    }
                }
            }
        }
    }

    return 0;
}
