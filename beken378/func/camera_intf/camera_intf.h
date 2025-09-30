#include <stdint.h>
#ifndef __CAMERA_INTF_H__
#define __CAMERA_INTF_H__


//#define USE_CAMERA              GC0328C_DEV

#define CAMERA_RESET_GPIO_INDEX		GPIO16
#define CAMERA_RESET_HIGH_VAL       1
#define CAMERA_RESET_LOW_VAL        0

#define EJPEG_DMA_CHNAL             GDMA_CHANNEL_5
#define EJPEG_DELAY_HTIMER_CHNAL    5
#define EJPEG_DELAY_HTIMER_VAL      (2)  // 2ms
#define USE_JTAG_FOR_DEBUG          1 // USE I2C2 and not I2C1!!!
#define I2C_WIRTE_TIMEOUT_COUNT     20

void camera_intf_sccb_write(uint8_t addr, uint8_t data);
void camera_intf_sccb_read(uint8_t addr, uint8_t *data);
uint8_t camera_intf_sccb_write2(uint8_t device_addr, uint8_t register_addr, uint8_t *data, uint8_t len);
uint8_t camera_intf_sccb_read2(uint8_t device_addr, uint8_t register_addr, uint8_t *data, uint8_t len);

#endif  