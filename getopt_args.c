#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int ret;
    char *filename = NULL;
    int number_a = 0;
    int number_b = 0;
    int add = 0;
    int usage = 0;

    while ((ret = getopt(argc, argv, "f:a:b:Ah")) != -1) {
        switch (ret) {
            case 'a':
                number_a = atoi(optarg);
            break;
            case 'b':
                number_b = atoi(optarg);
            break;
            case 'f':
                filename = optarg;
            break;
            case 'A':
                add = 1;
            break;
            case 'h':
            default:
                fprintf(stderr, "<%s> -a <number_a> -b <number_b> -A [add] -f <filename> -h [help]\n", argv[0]);
            return -1;
        }
    }

    if (add) {
        fprintf(stderr, "add [%d + %d = %d]\n", number_a, number_b, number_a + number_b);
    }
    if (filename) {
        fprintf(stderr, "filename is given in command line [%s]\n", filename);
    }
}
