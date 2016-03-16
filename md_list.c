#include "mbedtls/config.h"
#include "mbedtls/platform.h"
#include "mbedtls/md_internal.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
	int *md_list;

	md_list = mbedtls_md_list();
	if (!md_list) {
		fprintf(stderr, "failed to get mdlist\n");
		return -1;
	}

	while (*md_list) {
		mbedtls_md_info_t *md_info;

		md_info = mbedtls_md_info_from_type(*md_list);
		fprintf(stderr, "MD name: \t%s\n", md_info->name);
		fprintf(stderr, "MD size: \t%d\n", md_info->size);

		md_list ++;
	}

	return 0;
}
