#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pipefd[2];
	int ret;

	ret = pipe(pipefd);
	if (ret < 0) {
		fprintf(stderr, "failed to create a pipe\n");
		return -1;
	}

	pid_t child_pid;

	child_pid = fork();
	if (child_pid == 0) {
		char msg[100];

		close(pipefd[1]);
		read(pipefd[0], msg, sizeof(msg));
		printf("read %s\n", msg);
		exit(1);
	} else {
		char msg[] = "Hello ";

		close(pipefd[0]);
		write(pipefd[1], msg, sizeof(msg));
		exit(1);
	}

	return 0;
}
