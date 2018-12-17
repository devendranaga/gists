#include <iostream>
#include <vector>
#include <stdint.h>

struct sparse_matrix {
    uint8_t row;
    uint8_t col;
    int val;
};

int main()
{
    int sparse[6][6] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0},
    };

    std::vector<sparse_matrix> s;
    int i;
    int j;

    for (i = 0; i < 6; i ++) {
        for (j = 0; j < 6; j ++) {
            if (sparse[i][j] != 0) {
                struct sparse_matrix sp;

                sp.row = (uint8_t)i;
                sp.col = j;
                sp.val = sparse[i][j];

                s.push_back(sp);
            }
        }
    }

    std::vector<sparse_matrix>::const_iterator it;
    for (it = s.begin(); it != s.end(); it ++) {
        std::cout << "row: " << static_cast<int>((*it).row) << " col: " << static_cast<int>((*it).col) << " val: " << (*it).val << std::endl;
    }

    return 0;
}

