#include <stdio.h>
#include <dlfcn.h>

int func(void);

int main()
{
    int (*func)(void);
    void *dl_handle;

    dl_handle = dlopen("./libtest.so", RTLD_LAZY);
    if (!dl_handle) {
        fprintf(stderr, "no handle found \n");
        return -1;
    }

    func = dlsym(dl_handle, "function_a");
    printf("function %p\n", func);

    func();

    return 0;
}

