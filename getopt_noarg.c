#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int ret;
    int opt_t = 0;

    while ((ret = getopt(argc, argv, "t")) != -1) {
        switch (ret) {
            case 't':
                opt_t = 1;
            break;
            default:
                fprintf(stderr, "<%s> [-t]\n", argv[0]);
                return -1;
        }
    }

    if (opt_t) {
        fprintf(stderr, "opt_t is set\n");
    } else {
        fprintf(stderr, "opt_t is not set\n");
    }

    return 0;
}

