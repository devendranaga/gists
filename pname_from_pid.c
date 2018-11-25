#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char name[200];
    char buf[2048];
    char val[100];
    FILE *fp;
    int ret;

    if (argc != 2) {
        fprintf(stderr, "<%s> pid\n", argv[0]);
        return -1;
    }

    snprintf(name, sizeof(name), "/proc/%s/status", argv[1]);

    fp = fopen(name, "r");
    if (!fp) {
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        int i = 0;
        int j = 0;

        if (strstr(buf, "Name")) {
            i = strlen("Name:");

            while ((buf[i] != '\0') && (buf[i] == ' ')) {
                i ++;
            }

            while (buf[i] != '\n') {
                val[j] = buf[i];
                j ++;
                i ++;
            };

            val[j] = '\0';

        }
    }

    printf("name: %s\n", val);

    return 0;
}

