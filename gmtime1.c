#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    time_t now;
    struct tm t1;
    struct tm *t;

    now = time(0);

    t = gmtime_r(&now, &t1);
    if (!t) {
        printf("failure to gmtime %s\n", strerror(errno));
        return -1;
    }

    printf("%04d:%02d:%02d-%02d:%02d:%02d\n",
                    t->tm_year + 1900,
                    t->tm_mon + 1,
                    t->tm_mday,
                    t->tm_hour,
                    t->tm_min,
                    t->tm_sec);

    return 0;
}


