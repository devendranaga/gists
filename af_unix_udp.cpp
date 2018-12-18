#include <iostream>
#include <string>
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>

#define SERV_NAME "/tmp/unix_serv.sock"
#define CLI_NAME "/tmp/unix_client.sock"

class server {
    public:
        server(std::string name)
        {
            int ret;

            fd_ = socket(AF_UNIX, SOCK_DGRAM, 0);
            if (fd_ < 0) {
                return;
            }

            struct sockaddr_un serv;

            unlink(name.c_str());
            strcpy(serv.sun_path, name.c_str());
            serv.sun_family = AF_UNIX;

            ret = bind(fd_, (struct sockaddr *)&serv, sizeof(serv));
            if (ret < 0) {
                return;
            }
        }
        int recvFrom(char *str, int str_size)
        {
            return recvfrom(fd_, str, str_size, 0, NULL, NULL);
        }
    private:
        int fd_;

};

class client {
    public:

        client(std::string name, std::string servName)
        {
            int ret;

            fd_ = socket(AF_UNIX, SOCK_DGRAM, 0);
            if (fd_ < 0) {
                return;
            }

            struct sockaddr_un clientAddr;

            unlink(name.c_str());
            strcpy(clientAddr.sun_path, name.c_str());
            clientAddr.sun_family = AF_UNIX;

            ret = bind(fd_, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
            if (ret < 0) {
                return;
            }

            strcpy(serv_.sun_path, servName.c_str());
            serv_.sun_family = AF_UNIX;
        }
        int sendTo(const char *str, int str_size)
        {
            return sendto(fd_, str, str_size, 0, (struct sockaddr *)&serv_, sizeof(serv_));
        }

    private:
        struct sockaddr_un serv_;
        int fd_;
};

int main(int argc, char **argv)
{
    int ret;

    if (argc != 2) {
        std::cerr << argv[0] << " server / client " << std::endl;
        return -1;
    }

    if (std::string(argv[1]) == "server") {
        server s(SERV_NAME);

        while (1) {
            char string[100];
            ret = s.recvFrom(string, sizeof(string));
            if (ret < 0) {
                break;
            }
            std::cerr << "server: " << string << std::endl;
        }
    } else if (std::string(argv[1]) == "client") {
        client c(CLI_NAME, SERV_NAME);

        while (1) {
            std::string msg = "client says hi";
            sleep(1);

            std::cerr << "sending Hi .." << std::endl;
            c.sendTo(msg.c_str(), msg.length());
        }
    }
}

