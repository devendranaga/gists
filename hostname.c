#include <stdio.h>

int main()
{
    FILE *fp;
    const char *hostname = "/proc/sys/kernel/hostname";

    fp = fopen(hostname, "r");
    if (!fp) {
        return -1;
    }


    char host[80];

    fgets(host, sizeof(host), fp);

    fclose(fp);

    printf("hostname %s", host);

    return 0;
}
