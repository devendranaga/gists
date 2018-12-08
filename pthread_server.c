#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

struct thread_data {
    int sock;
};

void *thread_handle(void *data)
{
    struct thread_data *thread_data = data;
    int ret;

    while (1) {
        char rxbuf[1024];

        ret = recv(thread_data->sock, rxbuf, sizeof(rxbuf), 0);
        if (ret <= 0) {
            fprintf(stderr, "failed to recv %s\n", strerror(errno));
            break;
        }

        printf("data %s from client %d\n", (char *)rxbuf, thread_data->sock);
    }
}

int main(int argc, char **argv)
{
    struct sockaddr_in serv;
    int sock;
    int csock;
    struct thread_data data;
    pthread_t tid;
    int ret;

    if (argc != 3) {
        fprintf(stderr, "<%s> <ip> <port>\n", argv[0]);
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "failed to socket open %s\n", strerror(errno));
        return -1;
    }

    memset(&serv, 0, sizeof(serv));

    serv.sin_addr.s_addr = inet_addr(argv[1]);
    serv.sin_port = htons(atoi(argv[2]));
    serv.sin_family = AF_INET;

    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0) {
        fprintf(stderr, "failed to bind %s\n", strerror(errno));
        return -1;
    }

    ret = listen(sock, 4);
    if (ret < 0) {
        fprintf(stderr, "failed to listen %s\n", strerror(errno));
        return -1;
    }

    while (1) {
        csock = accept(sock, NULL, NULL);
        if (csock < 0) {
        fprintf(stderr, "failed to accept %s\n", strerror(errno));
            return -1;
        }

        struct thread_data *thr;

        thr = calloc(1, sizeof(struct thread_data));
        if (!thr) {
            fprintf(stderr, "failed to allocate %s\n", strerror(errno));
            return -1;
        }

        thr->sock = csock;

        ret = pthread_create(&tid, NULL, thread_handle, thr);
        if (ret < 0) {
            fprintf(stderr, "failed to pthrad_create %s\n", strerror(errno));
            return -1;
        }
    }

    return 0;
}


