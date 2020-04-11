#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

static void _get_rlimit(char *data, int flag)
{
    struct rlimit rlim;
    int ret;

    ret = getrlimit(flag, &rlim);
    if (ret < 0) {
        fprintf(stderr, "failed to getrlimit\n");
        return;
    }

    printf("[item %s]: soft: %lu hard: %lu\n", data, rlim.rlim_cur, rlim.rlim_max);
}


void set_max_stack_size(int n, char **argv)
{
    struct rlimit rlim;
    int ret;

    ret = getrlimit(RLIMIT_STACK, &rlim);
    if (ret < 0) {
        fprintf(stderr, "failed to getrlimit\n");
        return;
    }

    rlim.rlim_cur = strtol(argv[0], NULL, 10);

    ret = setrlimit(RLIMIT_STACK, &rlim);
    if (ret < 0) {
        fprintf(stderr, "failed to setrlimit\n");
        return;
    }
}

struct rlimit_list {
    char *string;
    int flag;
    void (*get_callback)(char *, int);
    void (*set_callback)(int n, char **rem_args);
} rlimit_list[] = {
    {"max_addr_space", RLIMIT_AS, _get_rlimit, NULL},
    {"max_file_size", RLIMIT_FSIZE, _get_rlimit, NULL},
    {"max_stack_size", RLIMIT_STACK, _get_rlimit, set_max_stack_size},
    {"max_cpu_time", RLIMIT_CPU, _get_rlimit, NULL},
    {"max_data_size", RLIMIT_DATA, _get_rlimit, NULL},
    {"max_core_size", RLIMIT_CORE, _get_rlimit, NULL},
    {"max_process", RLIMIT_NPROC, _get_rlimit, NULL},
    {"max_files", RLIMIT_NOFILE, _get_rlimit, NULL},
    {"max_memlock", RLIMIT_MEMLOCK, _get_rlimit, NULL},
    {"max_locks", RLIMIT_LOCKS, _get_rlimit, NULL},
    {"max_sigpending", RLIMIT_SIGPENDING, _get_rlimit, NULL},
    {"max_msgqueue", RLIMIT_MSGQUEUE, _get_rlimit, NULL},
    {"max_nice", RLIMIT_NICE, _get_rlimit, NULL},
    {"max_rtprio", RLIMIT_RTPRIO, _get_rlimit, NULL},
    {"max_rt_timeout", RLIMIT_RTTIME, _get_rlimit, NULL},
};

int main(int argc, char **argv)
{
    int i;

    if (!strcmp(argv[1], "get")) {
        for (i = 0; i < sizeof(rlimit_list) / sizeof(rlimit_list[0]); i ++) {
            rlimit_list[i].get_callback(rlimit_list[i].string, rlimit_list[i].flag);
        }
    } else if (!strcmp(argv[1], "set")) {
        for (i = 0; i < sizeof(rlimit_list) / sizeof(rlimit_list[0]); i ++) {
            if (!strcmp(rlimit_list[i].string, argv[2])) {
                if (rlimit_list[i].set_callback)
                    rlimit_list[i].set_callback(argc - 3, &argv[3]);
            }
        }
    }

    return 0;
}
