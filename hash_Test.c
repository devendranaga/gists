#include "mbedtls/config.h"
#include "mbedtls/platform.h"
#include "mbedtls/md5.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int digest_print(uint8_t *str, int len)
{
    int i;

    for (i = 0; i < len; i ++) {
        printf("%02x", str[i] & 0xff);
    }

    printf("\n");

    return 0;
}

int main(int argc, char **argv)
{
    int i;
    uint8_t digest[16];
              
    if (argc != 2) {
        printf("%s <string>\n", argv[0]);
        return -1;
    }
              
    mbedtls_md5(argv[1], strlen(argv[1]), digest);
              
    digest_print(digest, sizeof(digest));
              
    return 0;

}
