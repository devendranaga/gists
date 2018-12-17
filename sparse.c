#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int sparse[6][6] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0},
    };
    int i;
    int j;
    struct s_matrix {
        uint8_t row;
        uint8_t col;
        int val;
    };

    struct s_matrix *s = NULL;
    int counter = 0;

    for (i = 0; i < 6; i ++) {
        for (j = 0; j < 6; j ++) {
            if (sparse[i][j] != 0) {
                s = realloc(s, (counter + 1) * sizeof(struct s_matrix));
                if (!s) {
                    return -1;
                }

                s[counter].row = i;
                s[counter].col = j;
                s[counter].val = sparse[i][j];
                counter ++;
            }
        }
    }

    for (i = 0; i < counter; i ++) {
        printf("row: %d col: %d s->val %d\n", s[i].row, s[i].col, s[i].val);
    }

    printf("total array size %lu total allocated %lu\n", sizeof(sparse), sizeof(*s) * counter);

    free(s);

    return 0;
}

