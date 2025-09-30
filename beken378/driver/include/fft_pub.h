#include <stdint.h>
#ifndef _FFT_PUB_H_
#define _FFT_PUB_H_

#define FFT_FAILURE                (1)
#define FFT_SUCCESS                (0)

#define FFT_DEV_NAME                "fft"

#define FFT_CMD_MAGIC              (0xe260000)
enum
{
    CMD_FFT_BUSY = FFT_CMD_MAGIC + 1,
    CMD_FFT_ENABLE,
    CMD_FIR_SIGNLE_ENABLE
};

enum
{
    FFT_MODE_FFT,
    FFT_MODE_IFFT
};

typedef struct
{
    int mode;
    int16_t *inbuf;
    int16_t *outbuf;
    uint16_t size;
} input_fft_t;

typedef struct
{
    uint8_t fir_len;
    uint8_t fir_cwidth;
    uint8_t fir_dwidth;
    int16_t *coef;
    int16_t *input;
    int32_t *mac;
} input_fir_t;

/*******************************************************************************
* Function Declarations
*******************************************************************************/
void fft_init(void);
void fft_exit(void);
void fft_isr(void);
#endif //_FFT_PUB_H_
