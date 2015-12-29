#include <stdio.h>
#include <string.h>

char *strings[] = {
    "devendra",
    "devnaga",
    "opensource",
    "opensource software",
    "opensuse",
    "openworld",
    "python product",
    "python"
};

int len = sizeof(strings) / sizeof(strings[0]);

int wildcard_string_get(char *wildcard)
{
    int i;

    for (i = 0; i < len; i++) {
        char *found = strstr(strings[i], wildcard);
        if (found) {
            return i;
        }
    }

    return -1;
}

void getall(char *string)
{
    printf("got %s\n", string);
}

void wildcard_string_getall(char *wildcard, void (*getall)(char *string))
{
    int i;

    for (i = 0; i < len; i++) {
        if (strstr(strings[i], wildcard))
            getall(strings[i]);
    }
}

int main(int argc, char **argv)
{
    int i;
    int ret;
    int str_len = strlen(argv[1]);
    char wildarray[100];
    int j = 0, w = 0;

    memset(wildarray, 0, sizeof(wildarray));

    while (argv[1][j] != '\0' && argv[1][j] != '*') {
        wildarray[w] = argv[1][j];
        j++; w++;
    }

    wildarray[w] = '\0';

    wildcard_string_getall(wildarray, getall);

    return 0;
}

