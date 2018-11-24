#include <stdio.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

    int fd;

    fd = open("./test", O_RDWR | O_CREAT, S_IRWXU);
    if (fd < 0) {
        return -1;
    }

    printf("opened file although restricted in seccomp\n");

    return 0;
}

