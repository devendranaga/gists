#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
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
    char essid[65];

    memset(&req, 0, sizeof(req));
    strcpy(req.ifr_name, "wlxd0374533247a");
    req.u.essid.pointer = essid;
    req.u.essid.length = sizeof(essid);
    ret = ioctl(sock, SIOCGIWESSID, &req);
    if (ret < 0) {
        return -1;
    }

    printf("Essid: %s\n", essid);
}

