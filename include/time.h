struct timespec
{
    long sec, nsec;
};

int nanosleep(const struct timespec *t1, struct timespec *t2);
int sleep(int seconds);

