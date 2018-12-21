#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct crypto_struct {
    char name[40];
    char driver[40];
    char module[40];
    int priority;
    int refcnt;
    char selftest[40];
    char internal[40];
    char type[40];
    int block_size;
    int min_keysize;
    int max_keysize;
    int ivsize;
    char geniv[40];
    int chunksize;
    int walksize;
    int digest_size;
};

void parse_name_val(char *buf, char *name, char *val)
{
    int j;

    int namelen = strlen(name);

    j = namelen;

    while (buf[j] != '\0') {
        if ((buf[j] == ':') || (buf[j] == ' ')) {
            j ++;
        } else {
            break;
        }
    }
    strcpy(val, &buf[j]);
}

int main()
{
    FILE *fp;
    const char *crypto = "/proc/crypto";
    struct crypto_struct cr[80];
    int j;
    int i;

    fp = fopen(crypto, "r");
    if (!fp) {
        return -1;
    }

    char tmp[40];
    char buf[1024];

    j = 0;
    i = -1;
    while (fgets(buf, sizeof(buf), fp)) {
        buf[strlen(buf) - 1] = '\0';

        if (strstr(buf, "name")) {
            i ++;
            parse_name_val(buf, "name", cr[i].name);
        } else if (strstr(buf, "driver")) {
            parse_name_val(buf, "driver", cr[i].driver);
        } else if (strstr(buf, "module")) {
            parse_name_val(buf, "module", cr[i].module);
        } else if (strstr(buf, "priority")) {

            parse_name_val(buf, "priority", tmp);
            cr[i].priority = atoi(tmp);
        } else if (strstr(buf, "refcnt")) {

            parse_name_val(buf, "refcnt", tmp);
            cr[i].refcnt = atoi(tmp);
        } else if (strstr(buf, "selftest")) {
            parse_name_val(buf, "selftest", cr[i].selftest);
        } else if (strstr(buf, "internal")) {
            parse_name_val(buf, "internal", cr[i].internal);
        } else if (strstr(buf, "type")) {
            parse_name_val(buf, "type", cr[i].type);
        } else if (strstr(buf, "blocksize")) {

            parse_name_val(buf, "blocksize", tmp);
            cr[i].block_size = atoi(tmp);
        } else if (strstr(buf, "digestsize")) {

            parse_name_val(buf, "digestsize", tmp);
            cr[i].digest_size = atoi(tmp);
        } else if (strstr(buf, "ivsize")) {

            parse_name_val(buf, "ivsize", tmp);
            cr[i].ivsize = atoi(tmp);
        } else if (strstr(buf, "chunksize")) {

            parse_name_val(buf, "chunksize", tmp);
            cr[i].chunksize = atoi(tmp);
        } else if (strstr(buf, "walksize")) {

            parse_name_val(buf, "walksize", tmp);
            cr[i].walksize = atoi(tmp);
        } else if (strstr(buf, "min keysize")) {

            parse_name_val(buf, "min keysize", tmp);
            cr[i].min_keysize = atoi(tmp);
        } else if (strstr(buf, "max keysize")) {

            parse_name_val(buf, "max keysize", tmp);
            cr[i].max_keysize = atoi(tmp);
        }
    }

    int crypto_len = i;

    printf("crypto: {\n");
    for (i = 0; i < crypto_len; i ++) {
        printf("\t name: %s\n", cr[i].name);
        printf("\t driver: %s\n", cr[i].driver);
        printf("\t module: %s\n", cr[i].module);
        printf("\t priority: %d\n", cr[i].priority);
        printf("\t refcnt: %d\n", cr[i].refcnt);
        printf("\t selftest: %s\n", cr[i].selftest);
        printf("\t internal: %s\n", cr[i].internal);
        printf("\t type: %s\n", cr[i].type);
        printf("\t blocksize: %d\n", cr[i].block_size);
        printf("\t digest size: %d\n", cr[i].digest_size);
        printf("\t ivsize: %d\n", cr[i].ivsize);
        printf("\t chunksize: %d\n", cr[i].chunksize);
        printf("\t walksize: %d\n", cr[i].walksize);
        printf("\t min keysize: %d\n", cr[i].min_keysize);
        printf("\t max keysize: %d\n", cr[i].max_keysize);
        printf("\n");
    }
    printf("}\n");

    fclose(fp);
}
