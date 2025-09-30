#include <stdint.h>
#ifndef _SDIO_UTIL_H_
#define _SDIO_UTIL_H_

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern void su_init(SDIO_PTR sdio_ptr);

extern void su_push_node(LIST_HEADER_T *head, SDIO_NODE_PTR node);

extern SDIO_NODE_PTR su_pop_node(LIST_HEADER_T *head);

extern uint32_t su_get_node_count(LIST_HEADER_T *head);

extern uint32_t su_align_power2(uint32_t size);

#endif // _SDIO_UTIL_H_
