#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <linux/can/raw.h>

int main(int argc, char **argv)
{
    int fd;
    struct sockaddr_can can;
    struct can_frame canframe;
    struct ifreq ifr;
    int ret;

    fd = socket(AF_CAN, SOCK_RAW, CAN_RAW);
    if (fd < 0) {
        return -1;
    }

    strcpy(ifr.ifr_name, "vcan0");
    ret = ioctl(fd, SIOCGIFINDEX, &ifr);
    if (ret < 0) {
        return -1;
    }

    can.can_family = AF_CAN;
    can.can_ifindex = ifr.ifr_ifindex;

    ret = bind(fd, (struct sockaddr *)&can, sizeof(can));
    if (ret < 0) {
        return -1;
    }

#if 0
    canframe.can_id = 0x600;
    canframe.can_dlc = 8;
    canframe.data[0] = 0x44;
    canframe.data[1] = 0x44;
    canframe.data[2] = 0x44;
    canframe.data[3] = 0x44;
    canframe.data[4] = 0x44;
    canframe.data[5] = 0x44;
    canframe.data[6] = 0x44;
    canframe.data[7] = 0x44;
#endif

    struct can_filter f[2];

    f[0].can_id = 0x600;
    f[0].can_mask = CAN_SFF_MASK;

    f[1].can_id = 0x601;
    f[1].can_mask = CAN_SFF_MASK;

    ret = setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER, &f, sizeof(f));
    if (ret < 0) {
        return -1;
    }

    while (1) {
        sleep(1);

        ret = read(fd, (void *)&canframe, sizeof(canframe));
        if (ret < 0) {
            return -1;
        }

        printf("%02x %02x ", canframe.can_id, canframe.can_dlc);
        int i;

        for (i = 0; i < canframe.can_dlc; i ++) {
            printf("%02x:", canframe.data[i]);
        }
        printf("\n");
    }

    return 0;
}

