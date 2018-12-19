#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int new_tcp_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int new_udp_socket()
{
    return socket(AF_INET, SOCK_DGRAM, 0);
}

int new_tcp_unix_socket()
{
    return socket(AF_UNIX, SOCK_STREAM, 0);
}

int new_udp_unix_socket()
{
    return socket(AF_UNIX, SOCK_DGRAM, 0);
}

int destroy_socket(int sock)
{
    if (sock < 0)
        return -1;

    close(sock);

    return 0;
}

int new_tcp_server(const char *ip, int port, int n_conns)
{
    int ret;
    int sock;
    int set = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }

    struct sockaddr_in serv;

    serv.sin_addr.s_addr = inet_addr(ip);
    serv.sin_port = htons(port);
    serv.sin_family = AF_INET;

    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
    if (ret < 0) {
        goto err;
    }

    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0) {
        goto err;
    }

    ret = listen(sock, n_conns);
    if (ret < 0) {
        goto err;
    }

    return sock;

err:
    if (sock > 0)
        close(sock);

    return -1;
}

int accept_conn(int server_fd, char *dest_addr, uint32_t *dest_port)
{
    struct sockaddr_in dest;
    char *dest_str;
    socklen_t dest_len = sizeof(dest);
    int client_sock;

    if (!dest_addr || !dest_port) {
        return accept(server_fd, NULL, NULL);
    }

    client_sock = accept(server_fd, (struct sockaddr *)&dest, &dest_len);
    if (client_sock < 0) {
        return -1;
    }

    dest_str = inet_ntoa(dest.sin_addr);
    if (!dest_str) {
        goto err;
    }

    strcpy(dest_addr, dest_str);
    *dest_port = htons(dest.sin_port);

    return client_sock;

err:
    if (client_sock > 0) {
        close(client_sock);
    }

    return -1;
}

