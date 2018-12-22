#include <iostream>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class SocketUnix {
    public:
        SocketUnix();

        ~SocketUnix();

        int newUnixTcpServer(std::string path, int nConn);

        int newUnixTcpClient(std::string path);

        int newUnixUdpServer(std::string path);

        int newUnixUdpClient(std::string path);

        int destroySocket(int fd);

        int sendToUnix(int fd, std::string path, void *msg, int msgLen);

        int recvFromUnix(int fd, void *msg, int msgLen, std::string *path);
};


