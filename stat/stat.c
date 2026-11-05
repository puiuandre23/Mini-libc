// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	/* TODO: Implement stat(). */
	int x = syscall(4, path, buf);
	if(x < 0)
	{
		errno = -x;
		x = -1;
	}
	return x;
}
