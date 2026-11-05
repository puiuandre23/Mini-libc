#include <internal/syscall.h>
#include <errno.h>
#include <string.h>

int puts(const char *str)
{
    int len = strlen(str);
    int rez = syscall(1, 1, str, len);
    syscall(1, 1, "\n", 1);
    return rez;
}
