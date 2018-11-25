#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int sfd;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
        printf("afiled to sigprocmask\n");
        return -1;
    }

    sfd = signalfd(-1, &mask, 0);
    if (sfd < 0) {
        printf("failed to get signalfd\n");
        return -1;
    }

    while (1) {
        struct signalfd_siginfo sf;
        int ret;

        memset(&sf, 0, sizeof(sf));
        ret = read(sfd, &sf, sizeof(sf));
        if (ret != sizeof(sf)) {
            printf("invalid length of siginfo %d received\n", ret);
            return -1;
        }
        
        printf("pid %d signal value: %d signal code: %d\n",
        				sf.ssi_pid,
        				sf.ssi_signo,
        				sf.ssi_code);

        if (sf.ssi_signo == SIGQUIT) {
            printf("received termination signal\n");
        } else if (sf.ssi_signo == SIGINT) {
            printf("received interrupt\n");
        } else {
            printf("invalid signal %d\n", sf.ssi_signo);
        }
    }

    close(sfd);

    return 0;
}