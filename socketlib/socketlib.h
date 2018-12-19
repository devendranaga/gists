#ifndef __SOCKET_LIB_H__
#define __SOCKET_LIB_H__

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <print_api.h>

int new_tcp_socket();

int new_udp_socket();

int new_tcp_unix_socket();

int new_udp_unix_socket();

int destroy_socket(int sock);

int new_tcp_server(const char *ip, int port, int n_conns);

int accept_conn(int server_fd, int family, char *dest_addr, uint32_t *dest_port);

int new_udp_server(const char *ip, int port);

int new_tcp_unix_server(const char *path, int n_conns);

int new_udp_unix_server(const char *path);

int new_tcp_unix_client(const char *path);

int new_udp_unix_client(const char *path);

int send_message(int fd, int family, void *msg, int msglen, char *dest_addr, int dest_port);

#endif
