#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/wireless.h>

int main()
{
    int sock;
    int ret;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    struct iwreq req;

    memset(&req, 0, sizeof(req));
    strcpy(req.ifr_name, "wlxd0374533247a");
    ret = ioctl(sock, SIOCGIWFREQ, &req);
    if (ret < 0) {
        return -1;
    }

    printf("freq: %f\n", (double)req.u.freq.m/100000000);
}

