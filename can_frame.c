#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

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

    static int i = 0;

    while (1) {
        sleep(1);


        canframe.can_id = 0x600 + i;
        canframe.can_dlc = 8;
        canframe.data[0] = 0x44 + i;
        canframe.data[1] = 0x44 + i;
        canframe.data[2] = 0x44 + i;
        canframe.data[3] = 0x44 + i;
        canframe.data[4] = 0x44 + i;
        canframe.data[5] = 0x44 + i;
        canframe.data[6] = 0x44 + i;
        canframe.data[7] = 0x44 + i;

        printf("write %02x\n", canframe.can_id);
        ret = write(fd, (void *)&canframe, sizeof(canframe));
        if (ret < 0) {
            return -1;
        }

        i ++;

        if (i > 4) {
            i = 0;
        }
    }

    return 0;
}

