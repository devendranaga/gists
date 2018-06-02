#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v(20), v1, v2;
    int i;

    for (i = 0; i < 10; i ++) {
        v1.push_back(i);
        v2.push_back(10 - i);
    }

    std::cout << "v1 size:" << v1.size() <<std::endl
              << "v2.size:" << v2.size() << std::endl;

    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

    std::cout << "front:" << v1.front()
              << "back: " << v1.back() << std::endl;

    v.push_back(21);

    std::vector<int>::const_iterator iv;

    std::cout << "size:" << v.size() << std::endl;
    for (iv = v.begin(); iv != v.end(); iv ++) {
        std::cout << "iv:" << *iv << std::endl;
    }
}
