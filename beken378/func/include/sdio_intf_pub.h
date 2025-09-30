#include <stdint.h>
#ifndef _SDIO_INTF_PUB_H_
#define _SDIO_INTF_PUB_H_

#include "sdio_pub.h"
#include "ke_msg.h"
#include "tx_swdesc.h"

#define SDIO_INTF_FAILURE        ((uint32_t)-1)
#define SDIO_INTF_SUCCESS        (0)

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern uint32_t sdio_intf_init(void);
extern void sdio_emb_rxed_evt(int dummy);
extern uint32_t outbound_upload_data(uint8_t *buf_ptr, uint32_t len);
extern uint32_t sdio_get_free_node(uint8_t **buf_pptr, uint32_t buf_size);
extern void sdio_emb_rxed_evt(int dummy);
extern void inbound_cfm(void);
extern uint32_t sdio_emb_kmsg_fwd(struct ke_msg *msg);

extern uint32_t sdio_get_free_node_count(void);
extern uint32_t sdio_release_one_node(SDIO_NODE_PTR mem_node_ptr);

extern void sdio_trans_evt(int dummy);
extern SDIO_NODE_PTR sdio_get_rxed_node(void);
extern int sdio_trans_init(void);

#endif // _SDIO_INTF_PUB_H_


