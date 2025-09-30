#include <stdint.h>
#ifndef __JPEG_ENCODER_PUB_H__
#define __JPEG_ENCODER_PUB_H__

#if CFG_USE_CAMERA_INTF
#include "uart_pub.h"

#define EJPEG_FAILURE                (1)
#define EJPEG_SUCCESS                (0)

#define EJPEG_DEV_NAME               "ejpeg"
#define EJPEG_CMD_MAGIC              (0x0EBC0000)

#define EJPEG_DEBUG
#ifdef EJPEG_DEBUG
#define EJPEG_PRT                    os_printf
#else
#define EJPEG_PRT                    null_prf
#define EJPEG_WPRT                   null_prf
#endif

typedef struct ejpeg_desc
{
    uint8_t *rxbuf;

    void (*node_full_handler)(void *curptr, uint32_t newlen, uint32_t is_eof, uint32_t frame_len);
    void (*data_end_handler)(void);

    uint16_t rxbuf_len;
    uint16_t rx_read_len;
    uint32_t node_len;
    uint32_t sener_cfg;

    uint16_t x_pixel;
    uint16_t y_pixel;
    void (*start_frame_handler)(void);
    void (*end_frame_handler)(void);

    #if CFG_GENERAL_DMA
    void (*dma_rx_handler)(uint32_t);
    uint32_t dma_channel;
    #endif
} DJPEG_DESC_ST, *DJPEG_DESC_PTR;

enum
{
    EJPEG_CMD_SET_START_FRAME_INT = EJPEG_CMD_MAGIC + 1,
    EJPEG_CMD_SET_END_FRAME_INT,
    EJPEG_CMD_SET_MCLK_DIV,
    EJPEG_CMD_SET_VIDEO_BYTE_REVERSE,
    EJPEG_CMD_SELECT_YUV_FORMAT,
    EJPEG_CMD_SET_ENCODER_ENABLE,
    EJPEG_CMD_SET_X_PIXEL,
    EJPEG_CMD_ENABLE_ENC_SIZE,
    EJPEG_CMD_ENABLE_BITRATE_CTRL,
    EJPEG_CMD_SET_BITRATE_STEP,
    EJPEG_CMD_SET_HSYNC_REVERSE,
    EJPEG_CMD_SET_VSYNC_REVERSE,
    EJPEG_CMD_SET_Y_PIXEL,
    EJPEG_CMD_GET_TARGET_HIGH_BYTE,
    EJPEG_CMD_GET_TARTGE_LOW_BYTE,
    EJPEG_CMD_GET_FRAME_LEN,
};

#define Y_PIXEL_480                                  (60)  // Y * 8
#define X_PIXEL_640                                  (80)  // X * 8
#define Y_PIXEL_240                                  (30)  // Y * 8
#define X_PIXEL_320                                  (40)  // X * 8
#define Y_PIXEL_600                                  (75)  // Y * 8
#define X_PIXEL_800                                  (100) // X * 8
#define Y_PIXEL_720                                  (90)  // Y * 8
#define X_PIXEL_1280                                 (160) // X * 8

void ejpeg_init(void);
void ejpeg_exit(void);
void ejpeg_set_target_bitrate_size(uint32_t ppi_type);

#endif // CFG_USE_JPEG_ENCODER
#endif // __JPEG_ENCODER_PUB_H__
