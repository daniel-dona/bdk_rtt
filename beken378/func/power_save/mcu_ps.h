#include <stdint.h>
#ifndef _MCU_PS_H_
#define _MCU_PS_H_

//#define MCU_PS_DEBUG

#ifdef MCU_PS_DEBUG
#define MCU_PS_PRT                 os_printf

#else
#define MCU_PS_PRT                 os_null_printf

#endif

typedef struct {
#if (CFG_SUPPORT_ALIOS)
	uint64_t first_tick;
#else
	uint32_t first_tick;
#endif
	uint64_t first_tsf;
} MCU_PS_TSF;
typedef struct {
#if (CFG_SUPPORT_ALIOS)
	uint64_t fclk_tick;
#else
	uint32_t fclk_tick;
#endif
	uint32_t machw_tm;
} MCU_PS_MACHW_TM;

#endif

