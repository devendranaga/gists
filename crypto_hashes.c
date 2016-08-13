#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_alg.h>

int main(int argc, char **argv)
{
	int cli_fd;
	int ser_fd;

	struct sockaddr_alg sa = {
		.salg_family = AF_ALG,
		.salg_type = "hash",
		.salg_name = "sha1",
	};
	int i;
	char buf[1000];

	if (argc != 3) {
		fprintf(stderr, "%s [hash_function] [input]\n"
						"Where hash_function is one of the below\n"
						"\t 1. crct10dif\n"
						"\t 2. sha224\n"
						"\t 3. sha256\n"
						"\t 4. sha1\n"
						"\t 5. md5\n"
						"\t 6. md4\n",
						argv[0]);
		return -1;
	}

    strcpy(sa.salg_name, argv[1]);

	ser_fd = socket(AF_ALG, SOCK_SEQPACKET, 0);
	if (ser_fd < 0)
		return -1;

    int ret;

	ret = bind(ser_fd, (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0)
		return -1;

	cli_fd = accept(ser_fd, NULL, NULL);
	if (cli_fd < 0)
		return -1;

	write(cli_fd, argv[2], strlen(argv[2]));
	ret = read(cli_fd, buf, sizeof(buf));
	if (ret < 0)
		return -1;

	for (i = 0; i < ret; i ++) {
		printf("%02x", buf[i] & 0xff);
	}
	printf("\n");

	close(cli_fd);
	close(ser_fd);

	return 0;
}
