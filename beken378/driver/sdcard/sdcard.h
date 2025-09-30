#include <stdint.h>
#ifndef _SDCARD_H_
#define _SDCARD_H_

#if CFG_USE_SDCARD_HOST
#include "sdcard_pub.h"

typedef void (*SD_DETECT_FUN)(void);

typedef struct _sdcard_
{
    uint32_t  total_block;
    uint16_t  block_size;
    uint16_t  card_rca;
	uint16_t	Addr_shift_bit;
	uint8_t  	init_flag;
	uint8_t 	clk_cfg;
}SDCARD_S, *SDCARD_PTR;

/* API */
extern void sdcard_get_card_info(SDCARD_S *card_info);

extern uint32_t sdcard_open(uint32_t op_falag);

extern uint32_t sdcard_close(void);

extern uint32_t sdcard_read(char *user_buf, uint32_t count, uint32_t op_flag);

extern uint32_t sdcard_write(char *user_buf, uint32_t count, uint32_t op_flag);

extern uint32_t sdcard_ctrl(uint32_t cmd, void *parm);

#endif // CFG_USE_SDCARD_HOST

#endif
