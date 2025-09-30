#include <stdint.h>
#ifndef __SPI_DMA_PUB_H__
#define __SPI_DMA_PUB_H__

#if CFG_USE_HSLAVE_SPI
#include "rtos_pub.h"

#define SPIDMA_FAILURE                (1)
#define SPIDMA_SUCCESS                (0)

#define SPIDMA_DEV_NAME                "spidma"

#define SPIDMA_CMD_MAGIC              (0x0BCD0000)

enum
{
    SPIDMA_CMD_CONF_SCK_INV = SPIDMA_CMD_MAGIC + 1,
    SPIDMA_CMD_CONF_LSB_FIRST,
    SPIDMA_CMD_CONF_3WIRE_EN,
    SPIDMA_CMD_CONF_TIMEOUT_VAL,
    SPIDMA_CMD_CONF_RXBUF_ADDR,
    SPIDMA_CMD_CONF_RXBUF_LEN,
    SPIDMA_CMD_CONF_RXDATA_THRE,
    SPIDMA_CMD_GET_RXDATA_THRE,
    SPIDMA_CMD_GET_RXBUF_RDPTR,
    SPIDMA_CMD_SET_RXBUF_RDPTR,
    SPIDMA_CMD_GET_RXBUF_WRPTR,
    SPIDMA_CMD_CONF_TXBUF_ADDR,
    SPIDMA_CMD_CONF_TXBUF_LEN,
    SPIDMA_CMD_CONF_TXBUF_VALID,
    SPIDMA_CMD_GET_RXBUF_VALID_DATALEN,
    SPIDMA_CMD_START_TX_DMA,
    SPIDMA_CMD_STOP_TX_DMA,
};

#define SPIDMA_DESC_SCK_MODE_MASK    (0x1)
#define SPIDMA_DESC_SCK_MODE_POSI    (0)
#define SPIDMA_DESC_LSB_FIRST_MASK   (0x1)
#define SPIDMA_DESC_LSB_FIRST_POSI   (1)
#define SPIDMA_DESC_3WIRE_MODE_MASK  (0x1)
#define SPIDMA_DESC_3WIRE_MODE_POSI  (2)
#define SPIDMA_DESC_RX_THRED_MASK    (0xffffU)
#define SPIDMA_DESC_RX_THRED_POSI    (3)
#define SPIDMA_DESC_CALLBK_RD_NEWP_MASK    (0xffffU)
#define SPIDMA_DESC_CALLBK_CLR_RXTHRE_POSI   (16)
#define SPIDMA_DESC_CALLBK_CLR_RXTIO_POSI    (17)
#define SPIDMA_DESC_CALLBK_CLR_TXFIN_POSI    (18)

#if (CFG_SOC_NAME == SOC_BK7231)
typedef struct spidma_desc
{
    uint8_t *rxbuf;
    uint8_t *txbuf;
    uint16_t rxbuf_len;
    uint16_t txbuf_len;
    void (*rx_handler)(void *curptr, uint32_t newlen);
    void (*rx_timeout)(void);
    void (*tx_handler)(void);
    /* mode:     SPIDMA mode
     * bit[0]: SPIDMA sck clock invert
     *          0:  posedge sample data
     *          1:  negedge sample data
     * bit[1]: SPIDMA LSB transfer first
     *          0:  MSB transfer first
     *          1:  LSB transfer first
     * bit[2]: SPIDMA 3-wire mode
     *          0:  4-wire mode
     *          1:  3-wire mode
     * bit[3:19]: 16bit SPIDMA rxbuf threshold val
     */
    uint32_t mode;
    uint32_t timeout_val;
    uint32_t node_len;
} SPIDMA_DESC_ST, *SPIDMA_DESC_PTR;
#else
typedef struct spidma_desc
{
    uint8_t *rxbuf;
    
    void (*node_full_handler)(void *curptr, uint32_t newlen, uint32_t is_eof, uint32_t frame_len);
    void (*data_end_handler)(void);   

    uint16_t rxbuf_len;
    uint16_t rx_read_len;
    uint32_t node_len;
    

    uint8_t *txbuf;
    void (*tx_handler)(void);
   
    /* mode:     SPIDMA mode
     * bit[0]: SPIDMA sck clock invert
     *          0:  posedge sample data
     *          1:  negedge sample data
     * bit[1]: SPIDMA LSB transfer first
     *          0:  MSB transfer first
     *          1:  LSB transfer first
     * bit[2]: SPIDMA 3-wire mode
     *          0:  4-wire mode
     *          1:  3-wire mode
     * bit[3:19]: 16bit SPIDMA rxbuf threshold val
     */
    uint32_t mode;
    uint32_t timeout_val;
    uint32_t txbuf_len;
    void (*end_frame_handler)(void);
#if CFG_GENERAL_DMA
    void (*dma_rx_handler)(uint32_t);
    uint32_t dma_rx_channel;
    void (*dma_tx_handler)(uint32_t);
    uint32_t dma_tx_channel;
    
#endif
} SPIDMA_DESC_ST, *SPIDMA_DESC_PTR;

typedef struct spidma_tx_ {
    uint8_t *txbuf;
    uint32_t tx_len;
} SPIDMA_TXDMA_ST, *SPI_TXDMA_PTR;
#endif

#define SPIDMA_DEF_RXDATA_TIMEOUT_VAL       (800)  //  Unit is Tahb_clk
#define SPIDMA_DEF_RXDATA_THRE_INT          (4096) //(1024)

void spidma_init(void);
void spidma_uninit(void);

#endif // CFG_USE_HSLAVE_SPI

#endif

