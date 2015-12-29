#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

struct list {
    int value;
    uint32_t key;
    struct list *next;
};

struct hashtbl {
    int size;
    struct list **head;
};

typedef struct hashtbl hashtbl_t;

hashtbl_t *ht_create(int size)
{
    struct timeval tv;
    hashtbl_t *ht;

    ht = calloc(1, sizeof(hashtbl_t));
    if (!ht)
        return NULL;

    ht->size = size;

    ht->head = calloc(size, sizeof(struct list));
    if (!ht->head)
        return NULL;

    gettimeofday(&tv, 0);

    srand(tv.tv_usec);

    return ht;
}

int ht_hash(int val, hashtbl_t *ht)
{
    unsigned int hash = 5381;
    uint8_t val_int[4];
    int i;

    memcpy(val_int, &val, sizeof(val));

    for (i = 0; i < sizeof(int); i++)
        hash = ((hash << 5) + hash) + val_int[i];

    return hash % ht->size;
}

int ht_set(int val, hashtbl_t *ht)
{
    struct list *elem, *item;
    int hash;

    elem = calloc(1, sizeof(struct list));
    if (!elem)
        return -1;

    elem->value = val;

    hash = ht_hash(val, ht);

    item = ht->head[hash];

    if (!item)
        ht->head[hash] = elem;
    else
        item->next = elem;

    return 0;
}

void ht_for_each(hashtbl_t *ht)
{
    int i;
    struct list *elem;

    for (i = 0; i < ht->size; i++) {
        elem = ht->head[i];

        for (;elem; elem = elem->next)
            printf("value [%d]\n", elem->value);
    }
}

int main(int argc, char **argv)
{
    hashtbl_t *ht;

    ht = ht_create(1000);
    if (!ht)
        return -1;

    ht_set(atoi(argv[1]), ht);
    ht_set(atoi(argv[2]), ht);
    ht_set(atoi(argv[3]), ht);
    ht_set(atoi(argv[4]), ht);
    ht_set(atoi(argv[5]), ht);
    ht_set(atoi(argv[6]), ht);
    ht_set(atoi(argv[7]), ht);
    ht_for_each(ht);

    return 0;
}

