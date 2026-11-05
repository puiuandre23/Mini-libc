#include <internal/syscall.h>
#include <errno.h>
#include <time.h>

int nanosleep(const struct timespec *t1, struct timespec *t2)
{
    int x = syscall(35, t1, t2);
    return x;
}

int sleep(int seconds)
{
    struct timespec t1;
    t1.sec = seconds;
    t1.nsec = 0;
    struct timespec t2;
    nanosleep(&t1, &t2);
    return 0;
}

