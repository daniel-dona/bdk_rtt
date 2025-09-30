#include <stdint.h>
#ifndef _BK_SPI_FLASH_H_
#define _BK_SPI_FLASH_H_

int spi_flash_init(void);
void spi_flash_deinit(void);
uint32_t spi_flash_read_id(void);
int spi_flash_read(uint32_t addr, uint32_t size, uint8_t *dst);
int spi_flash_write(uint32_t addr, uint32_t size, uint8_t *src);
int spi_flash_erase(uint32_t addr, uint32_t size);
void spi_flash_protect(void);
void spi_flash_unprotect(void);

#endif //_BK_SPI_FLASH_H_