// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	/* TODO: Implement mmap(). */
	void *rez = (void *)syscall(9, addr, length, prot, flags, fd, offset);
	if((long)rez < 0)
	{
		errno =	-(long)rez;
		return MAP_FAILED;
	}
	return rez;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	void *rez = (void *)syscall(25, old_address, old_size, new_size, flags);
	if((long)rez < 0)
	{
		errno = -(long)rez;
		return MAP_FAILED;
	}
	return rez;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	long rez = syscall(11, addr, length);
	if(rez < 0)
	{
		errno = -rez;
		rez = -1;
	}
	return rez;
}
