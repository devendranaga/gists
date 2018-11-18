#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *thread_ctx)
{
    while (1) {
        sleep(1);
        printf("thread func..\n");
    }
}

int main()
{
    int ret;
    pthread_t tid;

    ret = pthread_create(&tid, NULL, thread_func, NULL);
    if (ret < 0) {
        fprintf(stderr, "failed to create thread\n");
        return -1;
    }

    pthread_join(tid, NULL);

    return 0;
}

