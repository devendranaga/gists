#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

class RandomGen {
    private:
        int Fd_;
    
    public:
        RandomGen();
        int getRandBytes(char *bytes);
        int getRandBytes(short *bytes);
        int getRandBytes(int *bytes);
        int getRandBytes(uint8_t *bytes, int len);
        ~RandomGen();
};

RandomGen::RandomGen()
{
    Fd_ = open("/dev/urandom", O_RDONLY);
    if (Fd_ < 0) {
        return;
    }
}

RandomGen::~RandomGen()
{
    if (Fd_ > 0) {
        close(Fd_);
    }
}

int RandomGen::getRandBytes(char *bytes)
{
    return read(Fd_, bytes, sizeof(char));
}

int RandomGen::getRandBytes(short *bytes)
{
    return read(Fd_, bytes, sizeof(short));
}

int RandomGen::getRandBytes(int *bytes)
{
    return read(Fd_, bytes, sizeof(int));
}

int RandomGen::getRandBytes(uint8_t *bytes, int len)
{
    return read(Fd_, bytes, len);
}

