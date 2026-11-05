// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	if(size == 0)
		return NULL;
	void *rez = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if((long)rez < 0)
	{
		errno = -(long)rez;
		return NULL;
	}
	mem_list_add(rez, size);
	return rez;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	if(size == 0)
		return NULL;
	void *rez = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if((long)rez < 0)
	{
		errno = -(long)rez;
		return NULL;
	}
	memset(rez, 0, nmemb * size);
	mem_list_add(rez, size);
	return rez;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	struct mem_list *p = mem_list_find(ptr);
	mem_list_del(ptr);
	munmap(ptr, p->len);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	struct mem_list *p = mem_list_find(ptr);
	void *new = mremap(ptr, p->len, size, MREMAP_MAYMOVE);
	if(new != ptr)
	{
		free(ptr);
		mem_list_add(new, size);
	}
	return new;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return realloc(ptr, nmemb * size);
}
