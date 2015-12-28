#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <sys/select.h>

fd_set allfd;
int maxfd;
int sfd_int;

int register_signal(sigset_t *sigmask, int sig, int *fd)
{
    sigemptyset(sigmask);
    sigaddset(sigmask, sig);

    sigprocmask(SIG_BLOCK, sigmask, NULL);
    *fd = signalfd(-1, sigmask, 0);
    if (*fd == -1) {
        printf("cannot get a signal fd\n");
        return -1;
    }


    FD_SET(*fd, &allfd);
    if (*fd > maxfd)
        maxfd = *fd;

    return 0;
}

int main()
{
    sigset_t mask_int;
    struct signalfd_siginfo siginfo;
    int ret;

    FD_ZERO(&allfd);

    register_signal(&mask_int, SIGINT, &sfd_int);

    while (1) {
        fd_set fds = allfd;

        ret = select(maxfd + 1, &allfd, NULL, NULL, 0);
        if (ret > 0) {
            struct signalfd_siginfo siginfo;

            if (FD_ISSET(sfd_int, &allfd)) {
                ret = read(sfd_int, &siginfo, sizeof(siginfo));
                if (ret == sizeof(siginfo)) {
                    printf("Got %d = %d\n", siginfo.ssi_signo, SIGINT);
                    close(sfd_int);
                    FD_CLR(sfd_int, &allfd);
                    sfd_int = signalfd(-1, &mask_int, 0);
                    if (sfd_int > maxfd)
                        maxfd = sfd_int;

                    FD_SET(sfd_int, &allfd);
                    sigaddset(&mask_int, SIGQUIT);
                    sigprocmask(SIG_BLOCK, &mask_int, NULL);
                }
            }
        }
    }

    return 0;
}

