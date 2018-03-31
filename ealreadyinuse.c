#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main()
{
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
	return -1;
    }

    int ret;
    struct sockaddr_in serv = {
        .sin_family = AF_INET,
	.sin_addr.s_addr = INADDR_ANY,
	.sin_port = htons(22),
    };

    ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0) {
	printf("error: %d %s\n", errno, strerror(errno));
	return -1;
    }

    return 0;
}

