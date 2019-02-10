#include <iostream>
#include <vector>


std::vector<int> operator+(std::vector<int> v1, std::vector<int> v2)
{
    size_t i;
    size_t size;
    size_t remaining;
    std::vector<int> v3;

    size = v1.size();
    if (v2.size() < size)
        size = v2.size();

    for (i = 0; i < size; i ++) {
        int p = v1[i] + v2[i];

        v3.push_back(p);
    }

    std::vector<int> &v = v2;
    remaining = v2.size() - v1.size();


    if (v1.size() > v2.size()) {
        remaining = v1.size() - v2.size();
        v = v1;
    }

    for (; i < size + remaining; i ++) {
        v3.push_back(v[i]);
    }

    return v3;
}

int main()
{
    std::vector<int> v1 {1, 2 ,3, 4};
    std::vector<int> v2 {11, 22, 33, 44, 99, 11};
    std::vector<int> v3;

    v3 = v1 + v2;

    std::vector<int>::const_iterator it;

    for (it = v3.begin(); it != v3.end(); it ++) {
        std::cout << *it << std::endl;
    }
}


