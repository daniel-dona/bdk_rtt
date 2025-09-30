#include <stdint.h>
#ifndef __RING_BUFFER_DMA_WR_H__
#define __RING_BUFFER_DMA_WR_H__


typedef struct rb_dma_rd_st
{
    uint8_t *address;     
    uint32_t capacity;    /**< memory capacity in bytes */
    uint32_t wp;          /**< write point in bytes     */
    uint32_t rp;          /**< read point in bytes      */
    uint32_t dma_ch;
}RB_DMA_WR_ST, *RB_DMA_WR_PTR;

void rb_init_dma_write(RB_DMA_WR_PTR rb, uint8_t *addr, uint32_t capacity, uint32_t ch);
void rb_clear_dma_write(RB_DMA_WR_PTR rb);
uint32_t rb_read_dma_write(RB_DMA_WR_PTR rb, uint8_t *buffer, uint32_t size, uint32_t count);
uint32_t rb_get_fill_size_dma_write(RB_DMA_WR_PTR rb);
uint32_t rb_get_free_size_dma_write(RB_DMA_WR_PTR rb);

#endif//__RING_BUFFER_DMA_RD_H__