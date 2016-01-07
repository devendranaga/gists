#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

int main(int argc, char **argv[])
{
    int ret;
    int stdin_fd = 0;
    int ep_fd;

    ep_fd = epoll_create1(EPOLL_CLOEXEC);
    if (ep_fd < 0)
        return -1;

    struct epoll_event ep_events;

    memset(&ep_events, 0, sizeof(struct epoll_event));

    ep_events.events = EPOLLIN;
    ep_events.data.fd = stdin_fd;

    if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, stdin_fd, &ep_events) < 0)
        return -1;

    for (;;) {
        int fds;
        struct epoll_event evt;

        fds = epoll_wait(ep_fd, &evt, 1, -1);
        printf("fds %d\n", fds);

        if (evt.data.fd == stdin_fd) {
            printf("read from stdin\n");
            char buf[100];
            read(stdin_fd, buf, sizeof(buf));
            printf("input %s\n", buf);
        }
    }

    return 0;
}

