// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	/* TODO: Implement truncate(). */
	int x = syscall(76, path, length);
	if(x < 0)
	{
		errno = -x;
		x = -1;
	}
	return x;
}
