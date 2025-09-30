#include <stdint.h>
#ifndef _STR_PUB_H_
#define _STR_PUB_H_

#include <stdarg.h>

uint32_t os_strlen(const char *str);

int32_t os_strcmp(const char *s1, const char *s2);

int32_t os_strncmp(const char *s1, const char *s2, const uint32_t n);

int32_t os_snprintf(char *buf, uint32_t size, const char *fmt, ...);

int32_t os_vsnprintf(char *buf, uint32_t size, const char *fmt, va_list ap);

char *os_strncpy(char *out, const char *in, const uint32_t n);

uint32_t os_strtoul(const char *nptr, char **endptr, int base);

char *os_strcpy(char *out, const char *in);

char *os_strchr(const char *s, int c);

char *os_strdup(const char *s);

int os_strcasecmp(const char *s1, const char *s2);

int os_strncasecmp(const char *s1, const char *s2, size_t n);

char *os_strrchr(const char *s, int c);

char *os_strstr(const char *haystack, const char *needle);

size_t os_strlcpy(char *dest, const char *src, size_t siz);

#endif // _STR_PUB_H_

// EOF
