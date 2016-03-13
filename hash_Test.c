#include "polarssl/config.h"
#include "polarssl/platform.h"
#include "polarssl/md5.h"
#include <stdio.h>
#include <stdint.h>
          
int digest_print(uint8_t *str, int len)
{
    int i;

    for (i = 0; i < len; i ++) {
        printf("%02x", str[i] & 0xff);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    int i;
    uint8_t digest[16];
              
  if (argc != 2) {
      printf("%s <string>\n", argv[0]);
      return -1;
  }
              
  md5(argv[1], strlen(argv[1]), digest);
              
  digest_print(digest, sizeof(digest));
              
  return 0;

}
