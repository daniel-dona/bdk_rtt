#include <stdint.h>
#ifndef _TARGET_UTIL_PUB_H_
#define _TARGET_UTIL_PUB_H_

extern void delay(int32_t num);
extern void delay_ms(uint32_t ms_count);
extern void delay_sec(uint32_t ms_count);
extern void delay_tick(uint32_t tick_count);

#endif // _TARGET_UTIL_PUB_H_
