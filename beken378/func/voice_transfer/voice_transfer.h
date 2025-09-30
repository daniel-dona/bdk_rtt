#include <stdint.h>
#ifndef __VOICE_TRANS_H__
#define __VOICE_TRANS_H__

typedef int (*video_transfer_send_func)(uint8_t *data, uint32_t len); 

uint32_t tvoice_transfer_init(video_transfer_send_func send_func);
uint32_t tvoice_transfer_deinit(void);

#endif // __VOICE_TRANS_H__