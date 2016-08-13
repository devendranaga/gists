#include <stdio.h>

int main(void)
{
	char data[64];
	FILE *fp;

	fp = popen("ls -l", "r");
	if (!fp) {
		fprintf(stderr, "failed to open ls -l \n");
		return -1;
	}

	while (fgets(data, sizeof(data), fp)) {
		fprintf(stderr, "%s", data);
	}

	pclose(fp);

	return 0;
}
