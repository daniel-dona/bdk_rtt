#include <stdint.h>
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__


typedef struct rb_st
{
    uint8_t *address;     
    uint32_t capacity;    /**< memory capacity in bytes */
    uint32_t wp;          /**< write point in bytes     */
    uint32_t rp;          /**< read point in bytes      */
}RB_ST, *RB_PTR;

void rb_init(RB_PTR rb, uint8_t *addr, uint32_t capacity);
void rb_clear(RB_PTR rb);
uint32_t rb_read(RB_PTR rb, uint8_t *buffer, uint32_t size, uint32_t count);
uint32_t rb_write(RB_PTR rb, uint8_t *buffer, uint32_t size, uint32_t count);
uint32_t rb_get_fill_size(RB_PTR rb);
uint32_t rb_get_free_size(RB_PTR rb);

#endif//__RING_BUFFER_H__
