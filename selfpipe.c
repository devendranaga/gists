#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/select.h>

int maxfd_all(int pipefd[10][2], int len)
{
    int maxfd = 0;
    int i;

    for (i = 0; i < len; i ++) {
        if (maxfd < pipefd[i][0])
            maxfd = pipefd[i][0];
    }

    return maxfd;
}

int main()
{
    pid_t pid;
    int i;
    int ret;
    int pipefd[10][2];
    fd_set allfd;
    fd_set rdset;
    int maxfd = 0;

    FD_ZERO(&rdset);

    for (i = 0; i < 10; i ++) {
        ret = pipe(pipefd[i]);

        printf("Read end %d max fd %d\n", pipefd[i][0], maxfd);
        FD_SET(pipefd[i][0], &rdset);
        if (maxfd < pipefd[i][0])
            maxfd = pipefd[i][0];

        pid = fork();
        if (pid != 0) {
            close(pipefd[i][1]);
        } else {
            close(pipefd[i][0]);
            for (i = 0; i < 100000000; i ++) ; 
            sleep(1);
            _exit(1);
        }
    }

    while (1) {
        allfd = rdset;

        maxfd = maxfd_all(pipefd, 10);

        if (maxfd <= 0) {
            break;
        }

        ret = select(maxfd + 1, &allfd, 0, 0, NULL);
        if (ret < 0) {
            perror("select");
            return -1;
        } else {
            for (i = 0; i < 10; i ++) {
                if (FD_ISSET(pipefd[i][0], &rdset)) {
                    printf("reap child.. %d \n", pipefd[i][0]);
                    waitpid(-1, NULL, WNOHANG);
                    //close(pipefd[i][0]);
                    FD_CLR(pipefd[i][0], &rdset);
                    pipefd[i][0] = -1;
                }
            }
        }
    }

    return 0;
}

