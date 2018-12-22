#include <iostream>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class SocketUnix {
    public:
        SocketUnix() {
        }

        ~SocketUnix() {
        }

        int newUnixTcpServer(std::string path, int nConn)
        {
            int fd;
            int ret;

            fd = socket(AF_UNIX, SOCK_STREAM, 0);
            if (fd < 0) {
                return -1;
            }

            unlink(path.c_str());

            struct sockaddr_un serv;

            strcpy(serv.sun_path, path.c_str());
            serv.sun_family = AF_UNIX;

            ret = bind(fd, (struct sockaddr *)&serv, sizeof(serv));
            if (ret < 0) {
                close(fd);
                return -1;
            }

            ret = listen(fd, nConn);
            if (ret < 0) {
                close(fd);
                return -1;
            }

            return fd;
        }

        int newUnixTcpClient(std::string path)
        {
            int fd;
            int ret;

            fd = socket(AF_UNIX, SOCK_STREAM, 0);
            if (fd < 0) {
                return -1;
            }

            struct sockaddr_un serv;

            strcpy(serv.sun_path, path.c_str());
            serv.sun_family = AF_UNIX;

            ret = connect(fd, (struct sockaddr *)&serv, sizeof(serv));
            if (ret < 0) {
                close(fd);
                return -1;
            }

            return fd;
        }

        int newUnixUdpServer(std::string path)
        {
            int fd;
            int ret;

            fd = socket(AF_UNIX, SOCK_DGRAM, 0);
            if (fd < 0) {
                return -1;
            }

            unlink(path.c_str());

            struct sockaddr_un serv;

            strcpy(serv.sun_path, path.c_str());
            serv.sun_family = AF_UNIX;

            ret = bind(fd, (struct sockaddr *)&serv, sizeof(serv));
            if (ret < 0) {
                return -1;
            }

            return fd;
        }

        int newUnixUdpClient(std::string path)
        {
            int fd;
            int ret;

            fd = socket(AF_UNIX, SOCK_DGRAM, 0);
            if (fd < 0) {
                return -1;
            }

            unlink(path.c_str());

            struct sockaddr_un serv;

            strcpy(serv.sun_path, path.c_str());
            serv.sun_family = AF_UNIX;

            ret = bind(fd, (struct sockaddr *)&serv, sizeof(serv));
            if (ret < 0) {
                return -1;
            }

            return fd;
        }

        int destroySocket(int fd)
        {
            return close(fd);
        }

        int sendToUnix(int fd, std::string path, void *msg, int msgLen)
        {
            struct sockaddr_un serv;

            strcpy(serv.sun_path, path.c_str());
            serv.sun_family = AF_UNIX;

            return sendto(fd, msg, msgLen, 0, (struct sockaddr *)&serv, sizeof(serv));
        }

        int recvFromUnix(int fd, void *msg, int msgLen, std::string *path)
        {
            struct sockaddr_un serv;
            socklen_t servLen = sizeof(struct sockaddr_un);
            int ret;

            ret = recvfrom(fd, msg, msgLen, 0, (struct sockaddr *)&serv, &servLen);
            if (ret < 0)
                return -1;

            if (path)
                *path = std::string(serv.sun_path);

            return ret;
        }


};


