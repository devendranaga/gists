#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *fp;
    const char *meminfo = "/proc/meminfo";
    int ret;
    int k;
    int i;
    char buf[1024];
    char *ptr;
    char memtotal[40];
    char memfree[40];
    int memtotal_int;
    int memfree_int;
    int memused;

    fp = fopen(meminfo, "r");
    if (!fp) {
        return -1;
    }

    memset(memtotal, 0, sizeof(memtotal));

    memtotal_int = 0;
    memfree_int = 0;

    while (fgets(buf, sizeof(buf), fp)) {
        buf[strlen(buf) - 1] = '\0';

        ptr = strstr(buf, "MemTotal:");
        if (ptr) {
            ptr += strlen("MemTotal:");
            i = 0;

            while (ptr[i] == ' ') {
                i ++;
            }

            k = 0;

            while (ptr[i] != ' ') {
                memtotal[k] = ptr[i];
                i ++;
                k ++;
            }

            memtotal[k] = '\0';

            memtotal_int = atoi(memtotal);
        }

        ptr = strstr(buf, "MemFree:");
        if (ptr) {
            ptr += strlen("MemFree:");
            i = 0;

            while (ptr[i] == ' ') {
                i ++;
            }

            k = 0;

            while (ptr[i] != ' ') {
                memfree[k] = ptr[i];
                i ++;
                k ++;
            }

            memfree[k] = '\0';

            memfree_int = atoi(memfree);
        }
    }

    memused = memtotal_int - memfree_int;

    printf("memtotal %f GB memfree %f GB memused %f GB\n", memtotal_int / (1024.0 * 1024), memfree_int / (1024.0 * 1024), memused / (1024.0 * 1024));

    fclose(fp);
}
