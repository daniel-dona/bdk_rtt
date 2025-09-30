#include <stdint.h>
#include "include.h"
#include "arm_arch.h"
#include <string.h>

#include <rtthread.h>

int32_t os_memcmp(const void *s1, const void *s2, uint32_t n)
{
    return memcmp(s1, s2, (unsigned int)n);
}

void *os_memmove(void *out, const void *in, uint32_t n)
{
    return memmove(out, in, n);
}

void *os_memcpy(void *out, const void *in, uint32_t n)
{
    return memcpy(out, in, n);
}

void *os_memset(void *b, int c, uint32_t len)
{
    return (void *)memset(b, c, (unsigned int)len);
}
#if (CFG_SUPPORT_RTT) && (CFG_SOC_NAME == SOC_BK7221U)
void *dtcm_malloc(size_t size)
{
	extern void *tcm_malloc(unsigned long size); 
    return (void *)tcm_malloc(size);
}
#endif
void *os_malloc(size_t size)
{
    return (void *)rt_malloc(size);
}

void * os_zalloc(size_t size)
{
	void *n = (void *)rt_malloc(size);
	if (n)
		os_memset(n, 0, size);
	return n;
}

void *os_realloc(void *ptr, size_t size)
{
	void *tmp;

	tmp = (void *)rt_malloc(size);
	if(tmp)
	{
		os_memcpy(tmp, ptr, size);
		rt_free(ptr);
	}

	return tmp;
}

void os_free(void *ptr)
{
    if(ptr)
    {
        rt_free(ptr);
    }
}

int os_memcmp_const(const void *a, const void *b, size_t len)
{
    return memcmp(a, b, len);
}
// EOF
