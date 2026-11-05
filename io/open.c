// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open(). */
    int fd;
    if (O_CREAT)
	{
        va_list args;
        va_start(args, flags);
        mode_t m = va_arg(args, mode_t);
        va_end(args);
        fd = syscall(2, filename, flags, m);
        if (fd < 0)
        {
            errno = -fd;
            fd = -1;
        }
    } else {
        fd = syscall(2, filename, flags);
        if (fd < 0)
        {
            errno = -fd;
            fd = -1;
        }
    }
    return fd;
}

