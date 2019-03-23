/**
 * example sigprocmask
 *
 * Author: Devendra Naga (devendra.aaru@gmail.com)
 *
 * LICENSE MIT
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    sigset_t set;
    int ret;

    sigemptyset(&set);

    // add SIGINT
    sigaddset(&set, SIGINT);

    ret = sigprocmask(SIG_BLOCK, &set, NULL);
    if (ret != 0) {
        perror("sigprocmask");
        return -1;
    }

    int count = 0;

    while (1) {
        printf("hello .. %d\n", count ++);
        sleep(1);
        if (count == 5) {
            break;
        }
    }

    ret = sigprocmask(SIG_UNBLOCK, &set, NULL);
    if (ret != 0) {
        perror("sigprocmask");
        return -1;
    }
}

