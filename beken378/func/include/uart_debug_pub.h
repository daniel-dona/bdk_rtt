#include <stdint.h>
#ifndef _UART_DEBUG_PUB_H_
#define _UART_DEBUG_PUB_H_

#include "uart_pub.h"

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern uint32_t udebug_has_ctrlc(void);
extern uint32_t udebug_wait_ctrlc_exit(void);
extern uint32_t uart_debug_init(void);

#endif // _UART_DEBUG_PUB_H_

