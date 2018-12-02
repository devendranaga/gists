#include <iostream>
#include <chrono>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *thread_contx)
{
    while (1) {
        sleep(1);
        std::cout <<" thread " << pthread_self() << std::endl;
    }
}

int main()
{
    pthread_attr_t attr;
    pthread_t thread_id;
    int ret;

    ret = pthread_attr_init(&attr);
    if (ret < 0) {
        return -1;
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (ret < 0) {
        return -1;
    }

    ret = pthread_create(&thread_id, &attr, thread_func, &thread_id);
    if (ret < 0) {
        return -1;
    }

    int detach_state = 0;

    ret = pthread_attr_getdetachstate(&attr, &detach_state);
    if (ret < 0) {
        return -1;
    }

    if (detach_state == PTHREAD_CREATE_DETACHED) {
        std::cout  << "thread created as detached..\n" ;
    } else if (detach_state == PTHREAD_CREATE_JOINABLE) {
        std::cout << "thread created as joniable\n";
    }

    if (detach_state == PTHREAD_CREATE_JOINABLE) {
        pthread_join(thread_id, NULL);
    } else {
        while (1) {
            sleep(1);
        }
    }

    return 0;
}

