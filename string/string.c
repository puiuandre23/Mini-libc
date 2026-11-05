// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	int len = strlen(source);
	int i;
	for (i = 0 ; i < len ; i++)
		destination[i] = source[i];
	destination[len] = 0;
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i;
	size_t len1 = strlen(destination);
	for (i = 0 ; i < len ; i++)
		destination[i] = source[i];
	if (len1 < len)
		destination[len] = 0;
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	int len1 = strlen(destination);
	int len2 = strlen(source);
	int i;
	for (i = 0 ; i < len2 ; i++)
		destination[len1 + i] = source[i];
	destination[len1 + len2] = 0;
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	int len1 = strlen(destination);
	size_t i;
	for (i = 0 ; i < len ; i++)
		destination[len1 + i] = source[i];
	destination[len1 + len] = 0;
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	int i;
	for (i = 0 ; str1[i] == str2[i] ; i++)
		if(str1[i] == 0 || str2[i] == 0)
			break;
	if(str1[i] == 0 && str2[i] == 0)
		return 0;
	if(str1[i] == 0)
		return -1;
	if(str2[i] == 0)
		return 1;
	if(str1[i] > str2[i])
		return 1;
	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	size_t i;
	for (i = 0 ; str1[i] == str2[i] && i < len ; i++)
		if(str1[i] == 0 || str2[i] == 0)
			break;
	if(i == len)
		return 0;
	if(str1[i] == 0 && str2[i] == 0)
		return 0;
	if(str1[i] == 0)
		return -1;
	if(str2[i] == 0)
		return 1;
	if(str1[i] > str2[i])
		return 1;
	return -1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	int i;
	int len = strlen(str);
	for(i = 0 ; i < len ; i++)
		if(str[i] == c)
			return (char *)(str + i);
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	int i;
	int len = strlen(str);
	for(i = len - 1 ; i >= 0 ; i--)
		if(str[i] == c)
			return (char *)(str + i);
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	int len1 = strlen(haystack);
	int len2 = strlen(needle);
	if(len1 < len2)
		return NULL;
	if(len1 == len2)
	{
		if(!strcmp(needle, haystack))
			return (char *)haystack;
		else
			return NULL;
	}
	int i, j;
	int found = 0, f;
	for(i = 0 ; i < len1 - len2 + 1 && !found ; i++)
	{
		f = 1;
		for(j = i ; j < i + len2 && f ; j++)
			if(haystack[j] != needle[j - i])
				f = 0;
		if(f == 1)
			found = 1;
	}
	if(found)
		return (char *)(haystack + i - 1);
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	int len1 = strlen(haystack);
	int len2 = strlen(needle);
	if(len1 < len2)
		return NULL;
	if(len1 == len2)
	{
		if(!strcmp(needle, haystack))
			return (char *)haystack;
		else
			return NULL;
	}
	int i, j;
	int found = 0, f;
	for(i = len1 - len2 ; i >= 0 && !found ; i--)
	{
		f = 1;
		for(j = i ; j < i + len2 && f ; j++)
			if(haystack[j] != needle[j - i])
				f = 0;
		if(f == 1)
			found = 1;
	}
	if(found)
		return (char *)(haystack + i + 1);
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	size_t i;
	for(i = 0 ; i < num ; i++)
		*((char *)destination + i) = *((char *)source + i);
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	size_t i;
	if((char *)destination < (char *)source)
	{
		for(i = 0 ; i < num ; i++)
			*((char *)destination + i) = *((char *)source + i);
	} else {
		if((char *)destination > (char *)source)
		{
			for(i = num ; i > 0 ; i--)
				*((char *)destination + i - 1) = *((char *)source + i - 1);
		}
	}
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	size_t i;
	for(i = 0 ; i < num ; i++)
		if(*((char *)ptr1 + i) != *((char *)ptr2 + i))
			break;
	if(i == num)
		return 0;
	if(*((char *)ptr1 + i) > *((char *)ptr2 + i))
		return 1;
	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	size_t i;
	for(i = 0 ; i < num ; i++)
		*((char *)source + i) = value;
	return source;
}
