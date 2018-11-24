#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <seccomp.h>

int main()
{
    scmp_filter_ctx ctx;

    ctx = seccomp_init(SCMP_ACT_KILL);

    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);

    seccomp_load(ctx);

    int fd;

    fd = open("./test", O_RDWR | O_CREAT, S_IRWXU);
    if (fd < 0) {
        printf("failed to create file \n");
        return -1;
    }

    printf("file is created\n");

    return 0;
}

