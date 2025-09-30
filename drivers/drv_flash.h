#include <stdint.h>
#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "typedef.h"
#include "flash_pub.h"

int beken_flash_init(void);
void beken_flash_read(uint32_t address, void *data, uint32_t size);
void beken_flash_write(uint32_t address, const void *data, uint32_t size);
void beken_flash_erase(uint32_t address);

#endif