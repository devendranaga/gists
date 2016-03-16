#include "mbedtls/config.h"
    #include "mbedtls/platform.h"
    #include "mbedtls/cipher.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(int argc, char **argv)
    {
	    int *cipher_list;
	    mbedtls_cipher_info_t *cipher_info;

	    cipher_list = mbedtls_cipher_list();
    	if (!cipher_list) {
	    	fprintf(stderr, "failed to get cipher list\n");
		    return -1;
	    }

	    while (*cipher_list) {
		    cipher_info = mbedtls_cipher_info_from_type(*cipher_list);
		    fprintf(stderr, "cipher name \t%s\n", cipher_info->name);
		    fprintf(stderr, "cipher keylen \t%d\n", cipher_info->key_bitlen);
	    	cipher_list ++;
	    }

	    return 0;
    }
