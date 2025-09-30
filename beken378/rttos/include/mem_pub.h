#include <stdint.h>
#ifndef _MEM_PUB_H_
#define _MEM_PUB_H_

#include <stdarg.h>
#include "typedef.h"

int32_t os_memcmp(const void *s1, const void *s2, uint32_t n);
void *os_memmove(void *out, const void *in, uint32_t n);
void *os_memcpy(void *out, const void *in, uint32_t n);
void *os_memset(void *b, int c, uint32_t len);
void os_mem_init(void);

void *os_malloc(size_t size);
void *os_zalloc(size_t size);
void *os_realloc(void *ptr, size_t size);
void os_free(void *ptr);

int os_memcmp_const(const void *a, const void *b, size_t len);

#endif // _MEM_PUB_H_

// EOF
