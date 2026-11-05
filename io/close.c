// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int close(int fd)
{
	/* TODO: Implement close(). */
	int x = syscall(3, fd);
	if(x < 0)
	{
		errno = -x;
		x = -1;
	}
	return x;
}
