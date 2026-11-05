// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	/* TODO: Implement ftruncate(). */
	int x = syscall(77, fd, length);
	if(x < 0)
	{
		errno = -x;
		x = -1;
	}
	return x;
}
