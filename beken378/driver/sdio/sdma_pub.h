#include <stdint.h>
#ifndef _SDMA_PUB_H_
#define _SDMA_PUB_H_

#define SDMA_INTERACT_WITH_HOST

typedef void (*TX_FUNC)(void);
typedef void (*CMD_FUNC)(void *buf, uint32_t len);
typedef void (*RX_FUNC)(uint32_t count);

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern void sdma_init(void);

extern void sdma_open(void);

extern void sdma_uninit(void);

extern void sdma_close(void);

#ifdef SDMA_INTERACT_WITH_HOST
extern uint32_t sdma_get_blk_len(void);
extern void sdma_set_tx_valid(void);
extern void sdma_clr_tx_valid(void);
extern void sdma_set_tx_dat_count(uint32_t val);
#endif // SDMA_INTERACT_WITH_HOST

extern void sdma_register_handler(TX_FUNC tx_callback,
                                  RX_FUNC rx_callback,
                                  CMD_FUNC cmd_callback);

extern uint32_t sdma_start_rx(uint8_t *buf, uint32_t len);
extern uint32_t sdma_start_tx(uint8_t *buf, uint32_t len);

extern uint32_t sdma_start_cmd(uint8_t *cmd, uint32_t len);
extern void sdma_fake_stop_dma(void);
extern void sdma_isr(void);
#endif // _SDMA_PUB_H_
