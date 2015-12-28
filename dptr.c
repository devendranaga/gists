#include <stdio.h>
#include <stdlib.h>

struct abc {
    int a;
    float f;
};

int main(int argc, char **argv)
{
    int i;
    struct abc **a;

    a = calloc(atoi(argv[1]), sizeof(struct abc));
    if (!a)
        return -1;

    for (i = 0; i < atoi(argv[1]); i++) {
        a[i] = calloc(1, sizeof(struct abc));
        a[i]->a = i;
        a[i]->f = i * 0.4;
    }

    for (i = 0; i < atoi(argv[1]); i++) {
        printf("a %d f %f\n", a[i]->a, a[i]->f);
        free(a[i]);
    }

    free(a);

    return 0;
}

