#ifndef __SOCKET_LIB_H__
#define __SOCKET_LIB_H__

// create new tcp socket
int new_tcp_socket();

// create new udp socket
int new_udp_socket();

// create new unix tcp socket
int new_tcp_unix_socket();

// create new unix udp socket
int new_udp_unix_socket();

// delete socket
int destroy_socket();

// create server based on `ip` and `port` and listen for `n_conn`
int new_tcp_server(const char *ip, int port, int n_conns);

// accept conn on the socket, and send out dest_addr and port back
int accept_conn(int server_fd, char *dest_addr, uint32_t *dest_port);

// create new udp server based off of `ip` and `port`
int new_udp_server(const char *ip, int port);

// create a new tcp unix server with given path
int new_tcp_unix_server(const char *path);

// create a new udp unix server with given path
int new_udp_unix_server(const char *path);

// create a new tcp unix client with given path
int new_tcp_unix_client(const char *path);

// create a new udp unix client with given path
int new_udp_unix_client(const char *path);

// send message on the fd
// dest_addr is valid for udp fd and unix fd
int send_message(int fd, void *msg, int msglen, char *dest_addr, int dest_port);

// recieve message on the fd 
// dest is valid for udp fd and unix fd
int recv_message(int fd, void *msg, int msglen, char *dest, uint32_t *dest_port);

// callback list
struct socket_loop_callbacks {
    int fd;
    void (*callback)(int fd, void *ptr);
    struct socket_loop_callbacks *next;
};

// privatepointer to socket_loop class
struct socket_loop {
    fd_set allfd;
    struct socket_loop_callbacks *callbacks;
};

// create a pointer to socket_loop and return
void *new_socket_loop();

// use the sock_loop returned and add fd to the fd_set
int add_fd_to_socket_loop(int fd, void *sock_loop, void *ptr, void (*callback)(int fd, void *ptr));

// remove fd from socket_loop
int del_fd_from_socket_loop(int fd, void *sock_loop, void *ptr, void (*callback)(int fd, void *ptr));

// run the socket loop and call callbacks 
int socket_loop_run(void *sock_loop);

// set multicast option on the socket for tx
int socket_set_multicast(int fd);

// subscribe for multicast data
int socket_add_to_mcast_group(int fd, char *mcast_ip);

// reuse socket address
int socket_reuse_addr(int fd);


#endif
