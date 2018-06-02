#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

extern "C" {
#include <unistd.h>
int getInt(int fd)
{
    int var;

    read(fd, &var, sizeof(var));

    return var;
}
}

int main()
{
    std::vector<unsigned int> a;
    struct timeval tv;
    int i;
    int fd;
    int *ptr;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        std::cout << "failed to open /dev/urandom" << std::endl;
        return -1;
    }

    for (i = 0; i < 100; i ++) {
        unsigned int var;

        var = getInt(fd);
        a.push_back(var);
    }

    std::sort(a.begin(), a.end());

    std::vector<unsigned int>::const_iterator t;

    for (t = a.begin(); t != a.end(); t ++) {
        std::cout << "a:" << *t << std::endl;
    }

    close(fd);

    std::cout << ptr << std::endl;

    return 0;
}