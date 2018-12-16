#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class pidFile {
    public:
        pidFile() { }
        ~pidFile() { }
        int setPidFile(std::string fileName)
        {
            int ret;

            fd_ = open(fileName.c_str(), O_RDWR);
            if (fd_ < 0) {
                return -1;
            }

            ret = lockf(fd_, F_TLOCK, 0);
            if (ret< 0) {
                return -1;
            }

            return 0;
        }

        int removePidFile()
        {
            lockf(fd_, F_ULOCK, 0);

            close(fd_);

            return 0;
        }

    private:
        int fd_;
};

int main(int argc, char **argv)
{
    pidFile p;
    int ret;

    if (argc != 2) {
        std::cerr << argv[0] << " filename" << std::endl;
        return -1;
    }


    ret = p.setPidFile(std::string(argv[1]));
    if (ret < 0) {
        std::cerr << "failed to acquire lock " << std::endl;
        return -1;
    }

    std::cout << "lock acquired successfully" << std::endl;

    // run another process and test locking..
    while (1);

    return 0;
}



