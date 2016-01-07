#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_link.h>

int main(int argc, char *argv[])
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;

    if (getifaddrs(&ifaddr) == -1)
        return -1;

    for (ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr) {
            char host[100];
            printf("ifname %s ", ifa->ifa_name);
            printf("\tfamily ");
            s = -1;
            if (ifa->ifa_addr->sa_family == AF_INET) {
                printf("AF_INET ");
            } else if (ifa->ifa_addr->sa_family == AF_INET6) {
                printf("AF_INET6 ");
            } else {
                printf("??? ");
            }
            if (s == 0)
                printf("\t\taddress %s", host);
            printf("\n");
        }
    }

    freeifaddrs(ifaddr);
    return 0;
}

