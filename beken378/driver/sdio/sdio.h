#include <stdint.h>
#ifndef _SDIO_H_
#define _SDIO_H_

#include "doubly_list.h"
#include "rwnx_config.h"

#define SDIO_DEBUG

#ifdef SDIO_DEBUG
#define SDIO_PRT                 os_null_printf //os_printf
#define SDIO_WPRT                warning_prf
#define STATIC
#else
#define SDIO_PRT                 os_null_printf
#define SDIO_WPRT                os_null_printf
#define STATIC                   static
#endif

#ifdef SDIO_DEBUG
#define MALLOC_MAGIC_LEN             (8)
#else
#define MALLOC_MAGIC_LEN             (0)
#endif

#define MALLOC_MAGIC_BYTE0           (0xAA)
#define MALLOC_MAGIC_BYTE1           (0xBB)

/*CMD BUFFER space: 64bytes*/
#define MAX_CONTENT_COUNT            (15)

#define DIR_TO_DTCM                  (0x55)
#define DIR_FROM_DTCM                (0xAA)

typedef struct _sdio_cmd
{
    uint8_t op_code;
    uint8_t len;
    uint8_t flag;
    uint8_t status;

    uint32_t content[MAX_CONTENT_COUNT];
} SDIO_CMD_S, *SDIO_CMD_PTR;


typedef struct _sdio_dcmd
{
    uint8_t op_code;
    uint8_t cmd_len;
    uint8_t flag;
    uint8_t status;

    uint16_t data_len;
#if FOR_SDIO_BLK_512
    uint16_t start_len;
    uint8_t seq;
    uint8_t reserve;
    uint16_t total_size;
    uint32_t content[MAX_CONTENT_COUNT - 2];
#else
    uint16_t reserve;
    uint32_t content[MAX_CONTENT_COUNT - 1];
#endif
} SDIO_DCMD_S, *SDIO_DCMD_PTR;

#define RX_NODE_OK                (0x1)
#define TX_NODE_OK                (0x2)
#define RX_NO_NODE                (0xA)
#define TX_NO_NODE                (0xB)

typedef struct _sdio_entity_
{
    uint16_t rx_status;
    uint16_t tx_status;
#if FOR_SDIO_BLK_512
    uint32_t tc_len;
    uint32_t rc_len;
    uint8_t tx_seq;
    uint8_t rx_seq;
#endif
    uint32_t rx_len;
    uint32_t tx_len;
    uint32_t r_hdl_len;
    uint32_t t_hdl_len;
    uint32_t tx_transaction_len;
    uint32_t rx_transaction_len;
    uint32_t transaction_len;

    SDIO_NODE_T snode[CELL_COUNT];

    LIST_HEADER_T tx_dat;
    LIST_HEADER_T txing_list;

    LIST_HEADER_T rx_dat;
    LIST_HEADER_T rxing_list;
    FUNCPTR rx_cb;

    LIST_HEADER_T free_nodes;

    SDIO_CMD_S cmd;
} SDIO_S, *SDIO_PTR;

#define OPC_WR_REG                       (0xC5)
#define OPC_RD_REG                       (0x5C)
#define OPC_WR_DTCM                      (0xE3)
#define OPC_RD_DTCM                      (0x3E)


/*hardware access: sdio internal register*/
#define SDIO_REG_CONFIG                  (0x10)
#define SDIO_CFG_BLK_MASK                   (0x07)
#define SDIO_CFG_BLK_POS                    (0)
#define SDIO_CFG_DATA_WIDTH_MASK            (0x03)
#define SDIO_CFG_DATA_WIDTH_POS             (4)

#define SDIO_REG_RETRY_DIR               (0x11)
#define RETRY_DIR_H2M                       (1 << 0)

#define SDIO_REG_DATA_STOP               (0x12)
#define DATA_STOP_RTX                       (1 << 0)

#define SDIO_REG_PROG_PROTECT1           (0x13)
#define PROG_PROTECT_WORD1                  (0xa5)

#define SDIO_REG_PROG_PROTECT2           (0x14)
#define PROG_PROTECT_WORD2                  (0xc3)

#define SDIO_REG_SYS_CTRL                (0x15)
#define SYS_CTRL_RESET                      (1 << 0)


/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern uint32_t sdio_open(uint32_t op_flag);

extern uint32_t sdio_close(void);

extern uint32_t sdio_read(char *user_buf, uint32_t count, uint32_t op_flag);

extern uint32_t sdio_write(char *user_buf, uint32_t count, uint32_t op_flag);

extern uint32_t sdio_ctrl(uint32_t cmd, void *parm);


#endif // _SDIO_H_
