#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <print_api.h>

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

int accept_conn(int server_fd, int family, char *dest_addr, uint32_t *dest_port)
{
    char *dest_str;
    int client_sock = -1;

    if (!dest_addr) {
        return accept(server_fd, NULL, NULL);
    }

    if (family == AF_INET) {
        struct sockaddr_in dest;
        socklen_t dest_len = sizeof(dest);

        client_sock = accept(server_fd, (struct sockaddr *)&dest, &dest_len);
        if (client_sock < 0) {
            return -1;
        }

        dest_str = inet_ntoa(dest.sin_addr);
        if (!dest_str) {
            SOCKLIB_ERR("sockLib: failed to inet_ntoa @ %s %u\n", __func__, __LINE__);
            goto err;
        }

        strcpy(dest_addr, dest_str);
        if (dest_port)
            *dest_port = htons(dest.sin_port);

    } else if (family == AF_UNIX) {
        struct sockaddr_un dest;
        socklen_t dest_len = sizeof(struct sockaddr_un);

        client_sock = accept(server_fd, (struct sockaddr *)&dest, &dest_len);
        if (client_sock < 0) {
            return -1;
        }

        strcpy(dest_addr, dest.sun_path);
    }

    return client_sock;

err:
    if (client_sock > 0) {
        close(client_sock);
    }

    return -1;
}

int new_udp_server(const char *ip, int port)
{
    struct sockaddr_in serv;
    int ret;
    int sock;
    int set = 1;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    serv.sin_addr.s_addr = inet_addr(ip);
    serv.sin_port = htons(port);

    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &set, sizeof(set));
    if (ret < 0) {
        goto err;
    }

    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0) {
        goto err;
    }

    return sock;

err:
    if (sock > 0) {
        close(sock);
    }

    return -1;
}

int new_tcp_unix_server(const char *path, int n_conns)
{
    struct sockaddr_un serv;
    int sock;
    int ret;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }

    unlink(path);
    strcpy(serv.sun_path, path);
    serv.sun_family = AF_UNIX;

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
    if (sock > 0) {
        close(sock);
    }

    return -1;
}

int new_udp_unix_server(const char *path)
{
    struct sockaddr_un serv;
    int sock;
    int ret;

    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    unlink(path);
    strcpy(serv.sun_path, path);
    serv.sun_family = AF_UNIX;

    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0) {
        goto err;
    }

    return sock;

err:
    if (sock > 0) {
        close(sock);
    }

    return -1;
}

int new_tcp_unix_client(const char *path)
{
    struct sockaddr_un addr;
    int sock;
    int ret;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }

    strcpy(addr.sun_path, path);
    addr.sun_family = AF_UNIX;

    ret = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        goto err;
    }

    return sock;
err:
    if (sock > 0) {
        close(sock);
    }

    return -1;
}

int new_udp_unix_client(const char *path)
{
    struct sockaddr_un addr;
    int sock;
    int ret;

    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    unlink(path);
    strcpy(addr.sun_path, path);
    addr.sun_family = AF_UNIX;

    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        goto err;
    }

    return sock;
err:
    if (sock > 0) {
        close(sock);
    }

    return -1;
}

int send_message(int fd, int family, void *msg, int msglen, char *dest_addr, int dest_port)
{
    if (family == AF_INET) {
        struct sockaddr_in dest;

        if (dest_addr) {
            dest.sin_addr.s_addr = inet_addr(dest_addr);
            dest.sin_port = htons(dest_port);
            dest.sin_family = AF_INET;

            return sendto(fd, msg, msglen, 0, (struct sockaddr *)&dest, sizeof(dest));
        } else {
            return send(fd, msg, msglen, 0);
        }
    } else if (family == AF_UNIX) {
        struct sockaddr_un dest;

        if (dest_addr) {
            strcpy(dest.sun_path, dest_addr);
            dest.sun_family = AF_UNIX;

            return sendto(fd, msg, msglen, 0, (struct sockaddr *)&dest, sizeof(dest));
        } else {
            return send(fd, msg, msglen, 0);
        }
    }

    return -1;
}
