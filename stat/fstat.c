// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	/* TODO: Implement fstat(). */
	int x = syscall(5, fd, st);
	if(x < 0)
	{
		errno = -x;
		x = -1;
	}
	return x;
}
