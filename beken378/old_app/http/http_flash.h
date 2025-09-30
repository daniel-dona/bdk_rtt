#include <stdint.h>
#include "drv_model_pub.h"
#include "BkDriverFlash.h"

#define HTTP_WR_TO_FLASH        1

typedef struct http_data_st{
    uint32_t http_total;
    uint8_t do_data;
    #if HTTP_WR_TO_FLASH
    uint8_t *wr_buf ;
    uint8_t *wr_tmp_buf;
    uint16_t wr_last_len ;
    uint32_t flash_address;
    bk_logic_partition_t *pt;
    #endif
    DD_HANDLE flash_hdl;
}HTTP_DATA_ST;

#define TCP_LEN_MAX             1460
#define HTTP_FLASH_ADDR         0xff000

extern  void store_block (unsigned block, uint8_t * src, unsigned len);
#define WR_BUF_MAX 1048

extern HTTP_DATA_ST *bk_http_ptr;
