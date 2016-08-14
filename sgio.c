#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>

int main(int argc, char **argv)
{
	int fd;

    if (argc < 2) {
		fprintf(stderr, "%s [filename] [content]\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU);
	if (fd < 0) {
		fprintf(stderr, "failed to open %s\n", argv[1]);
		return -1;
	}

	int i;
	int count = 0;
	struct iovec iov[argc - 1];

	for (i = 2; i < argc; i ++) {
		iov[i - 2].iov_base = argv[i];
		iov[i - 2].iov_len = strlen(argv[i]);
		count ++;
	}

    char newline_str[] =  "\n";

    iov[count].iov_base = newline_str;
	iov[count].iov_len = strlen(newline_str);
	count ++;

	writev(fd, iov, count);

	close(fd);
}
