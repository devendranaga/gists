#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define SHM_NAME "/test_shm"
#define SHM_BYTES_MAX (1024 * 1024)
#define FIFO_NAME "/test_fifo"

static int fifd;
static int fd;

int intr_reader()
{
    int intr = 1;

    return write(fifd, &intr, sizeof(int));
}

int wait_for_intr()
{
    int intr = 0;
    int ret;

    ret = read(fifd, &intr, sizeof(intr));
    if (ret <= 0) {
        return -1;
    }

    return intr == 1;
}

void* mmap_create_buf()
{
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fd < 0) {
        perror("shm_open");
        return NULL;
    }

    ftruncate(fd, SHM_BYTES_MAX);

    void *addr;

    addr = mmap(NULL, SHM_BYTES_MAX, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    return addr;
}

void* mmap_attach_buf()
{
    fd = shm_open(SHM_NAME, O_RDWR, 0);
    if (fd < 0) {
        perror("shm_open");
        return NULL;
    }

    void *addr;

    addr = mmap(NULL, SHM_BYTES_MAX, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    return addr;
}

int fifo_create()
{
    int ret;

    unlink(FIFO_NAME);

    ret = mkfifo(FIFO_NAME, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (ret < 0) {
        perror("mkfifo");
        return -1;
    }

    fifd = open(FIFO_NAME, O_RDWR);
    if (fifd < 0) {
        perror("open");
        return -1;
    }

    return 0;
}

int fifo_attach()
{
    fifd = open(FIFO_NAME, O_RDWR);
    if (fifd < 0) {
        perror("open");
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int ret;
    void *addr;

    if (argc != 2) {
        fprintf(stderr, "<%s> producer/consumer\n", argv[0]);
        return -1;
    }

    if (!strcmp(argv[1], "producer")) {
        addr = mmap_create_buf();
        if (!addr) {
            return -1;
        }

        ret = fifo_create();
        if (ret < 0) {
            return -1;
        }

        while (1) {
            strcpy(addr, "Hello ");

            intr_reader();
            sleep(1);
        }
    } else if (!strcmp(argv[1], "consumer")) {
        addr = mmap_attach_buf();
        if (!addr) {
            return -1;
        }

        ret = fifo_attach();
        if (ret < 0) {
            return -1;
        }

        while (1) {
            wait_for_intr();
            printf("data from prod: %s\n", addr);

            memset(addr, 0, 10);
        }
    }
}
