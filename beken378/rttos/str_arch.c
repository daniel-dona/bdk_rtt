#include <stdint.h>
#include "include.h"
#include "arm_arch.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "str_pub.h"
#include "mem_pub.h"

char *os_strchr(const char *s, int c)
{
    return strchr(s, c);
}

uint32_t os_strlen(const char *str)
{
    return strlen(str);
}

int32_t os_strcmp(const char *s1, const char *s2)
{
    return strcmp(s1, s2);
}

uint32_t os_strtoul(const char *nptr, char **endptr, int base)
{
    return strtoul(nptr, endptr, base);
}

char *os_strcpy(char *out, const char *in)
{
    return strcpy(out, in);
}

char *os_strncpy(char *out, const char *in, const uint32_t n)
{
    return strncpy(out, in, (unsigned int)n);
}

size_t os_strlcpy(char *dest, const char *src, size_t siz)
{
    const char *s = src;
    size_t left = siz;

    if (left)
    {
        /* Copy string up to the maximum size of the dest buffer */
        while (--left != 0)
        {
            if ((*dest++ = *s++) == '\0')
                break;
        }
    }

    if (left == 0)
    {
        /* Not enough room for the string; force NUL-termination */
        if (siz != 0)
            *dest = '\0';

        while (*s++)
            ; /* determine total src string length */
    }

    return s - src - 1;
}

int32_t os_strncmp(const char *s1, const char *s2, const uint32_t n)
{
    return strncmp(s1, s2, (unsigned int)n);
}

int32_t os_snprintf(char *buf, uint32_t size, const char *fmt, ...)
{
    va_list args;
    int32_t rc;

    va_start(args, fmt);
    rc = vsnprintf(buf, size, fmt, args);
    va_end(args);

    /* if want to print more than the limitation */
    if (rc > size)
        rc = (int32_t)size - rc;

    return rc;
}

int32_t os_vsnprintf(char *buf, uint32_t size, const char *fmt, va_list ap)
{
    return vsnprintf(buf, size, fmt, ap);
}

char *os_strdup(const char *s)
{
    char *res;
    size_t len;

    if (s == NULL)
        return NULL;

    len = os_strlen(s);
    res = os_malloc(len + 1);
    if (res)
        os_memcpy(res, s, len + 1);

    return res;
}


int os_strcasecmp(const char *s1, const char *s2)
{
    /*
     * Ignoring case is not required for main functionality, so just use
     * the case sensitive version of the function.
     */
    return os_strcmp(s1, s2);
}


int os_strncasecmp(const char *s1, const char *s2, size_t n)
{
    /*
     * Ignoring case is not required for main functionality, so just use
     * the case sensitive version of the function.
     */
    return os_strncmp(s1, s2, n);
}

char *os_strrchr(const char *s, int c)
{
    return strrchr(s, c);
}

char *os_strstr(const char *haystack, const char *needle)
{
    return NULL;
}
// EOF
