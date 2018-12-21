#include <stdio.h>
#include <unistd.h>

struct sysconf_params {
    char *name;
    int param;
    int val;
};

int main()
{
    struct sysconf_params sysconf_args[] = {
        {"_SC_ARG_MAX", _SC_ARG_MAX, 0},
        {"_SC_OPEN_MAX", _SC_OPEN_MAX, 0},
        {"_SC_STREAM_MAX", _SC_STREAM_MAX, 0},
        {"_SC_TZNAME_MAX", _SC_TZNAME_MAX, 0},
        {"_SC_NGROUPS_MAX", _SC_NGROUPS_MAX, 0},
        {"_SC_JOB_CONTROL", _SC_JOB_CONTROL, 0},
        {"_SC_SAVED_IDS", _SC_SAVED_IDS, 0},
        {"_SC_VERSION", _SC_VERSION, 0},
        {"_SC_CLK_TCK", _SC_CLK_TCK, 0},
        {"_SC_CHARCLASS_NAME_MAX", _SC_CHARCLASS_NAME_MAX, 0},
        {"_SC_REALTIME_SIGNALS", _SC_REALTIME_SIGNALS, 0},
        {"_SC_PRIORITY_SCHEDULING", _SC_PRIORITY_SCHEDULING, 0},
        {"_SC_TIMERS", _SC_TIMERS, 0},
        {"_SC_ASYNCHRONOUS_IO", _SC_ASYNCHRONOUS_IO, 0},
        {"_SC_PRIORITIZED_IO", _SC_PRIORITIZED_IO, 0},
        {"_SC_MEMLOCK", _SC_MEMLOCK, 0},
        {"_SC_MEMLOCK_RANGE", _SC_MEMLOCK_RANGE, 0},
        {"_SC_SEMAPHORES", _SC_SEMAPHORES, 0},
        {"_SC_MQ_OPEN_MAX", _SC_MQ_OPEN_MAX, 0},
        {"_SC_MQ_PRIO_MAX", _SC_MQ_PRIO_MAX, 0},
        {"_SC_SEM_NSEMS_MAX", _SC_SEM_NSEMS_MAX, 0},
        {"_SC_SEM_VALUE_MAX", _SC_SEM_VALUE_MAX, 0},
        {"_SC_TIMER_MAX", _SC_TIMER_MAX, 0},
        {"_SC_LOGIN_NAME_MAX", _SC_LOGIN_NAME_MAX, 0},
        {"_SC_THREAD_STACK_MIN", _SC_THREAD_STACK_MIN, 0},
        {"_SC_THREAD_THREADS_MAX", _SC_THREAD_THREADS_MAX, 0},
        {"_SC_LINE_MAX", _SC_LINE_MAX, 0},
        {"_SC_PAGESIZE", _SC_PAGESIZE, 0},
    };
    int i;

    for (i = 0; i < sizeof(sysconf_args) / sizeof(sysconf_args[0]); i ++) {
        sysconf_args[i].val = sysconf(sysconf_args[i].param);
    }

    for (i = 0; i < sizeof(sysconf_args) / sizeof(sysconf_args[0]); i ++) {
        printf("sysconf(%s) \t : %d\n", sysconf_args[i].name, sysconf_args[i].val);
    }

}

