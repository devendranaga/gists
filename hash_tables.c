/***
 * @simple hash table implementation in C
 *
 * Author: Dev Naga <devendra.aaru@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * List elements
 */
struct list_elem {
    void *spec_data;
    struct list_elem *next;
};

/**
 * Hash table
 */
struct hash_list {
    struct list_elem *item;
};

static int table_size;
static struct hash_list *hlist;

/**
 * Init the hash tables witha pre-defined table
 */
int hlist_init(int hlist_size)
{
    hlist = calloc(hlist_size, sizeof(struct hash_list));
    if (!hlist) {
        return -1;
    }

    table_size = hlist_size;
    return 0;
}

/**
 * Hash the data with a simple addition of characters
 */
static int hlist_hash_data(char *hash_str)
{
    int hash = 0;
    int i;

    for (i = 0; i < strlen(hash_str); i ++) {
        hash += hash_str[i];
    }

    return hash % table_size;
}

static int hlist_add_item_new(int index, void *item)
{
    hlist[index].item = calloc(1, sizeof(struct list_elem));
    if (!hlist[index].item) {
        return -1;
    }

    hlist[index].item->spec_data = item;
    hlist[index].item->next = NULL;

    return 0;
}

static int hlist_add_item_append(int index, void *item)
{
    struct list_elem *last, *iter;

    iter = hlist[index].item;
    last = iter;
    while (iter) {
       last = iter;
       iter = iter->next;
    }

    struct list_elem *new;

    new = calloc(1, sizeof(struct list_elem));
    if (!new) {
        return -1;
    }

    new->spec_data = item;
    last->next = new;

    return 0;
}

/**
 * Find item in the hash tables if exist
 */
int hlist_find_item(void *item, int (*compare)(void *a, void *b))
{
    int i;

    for (i = 0; i < table_size; i ++) {
        struct list_elem *list;
        int res;

        for (list = hlist[i].item; list; list = list->next) {
            res = compare(item, list->spec_data);
            if (res) {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * Add an item in list.. append if already hashed to same data, add new if does not
 */
int hlist_add_item(void *item, char *hash_str)
{
    int index;

    index = hlist_hash_data(hash_str);

    if (hlist[index].item == NULL) {
        hlist_add_item_new(index, item);
    } else {
        hlist_add_item_append(index, item);
    }

    return 0;
}

/**
 * Print hash table elements
 */
void hlist_print(void (*data_callback)(void *data))
{
   int i;

   for (i = 0; i < table_size; i ++) {
       struct list_elem *list;

       printf("hash item: <%d>\n", i);
       for (list = hlist[i].item; list; list = list->next) {
           printf("\t list->spec_data <%p>\n", list->spec_data);
           data_callback(list->spec_data);
       }
   }
}

/***
 * Test program
 */
void print_items(void *data)
{
    //printf("item : <%s>\n", data);
}

int compare_item(void *a, void *b)
{
    char *a_1 = a;
    char *a_2 = b;

    return (strcmp(a_1, a_2) == 0);
}

int main(int argc, char **argv)
{
    int i;

    hlist_init(20);

    for (i = 1; i <= argc - 1; i ++) {
        if (!hlist_find_item(argv[i], compare_item)) {
            hlist_add_item(argv[i], argv[i]);
        }
    }

    hlist_print(print_items);

    return 0;
}
