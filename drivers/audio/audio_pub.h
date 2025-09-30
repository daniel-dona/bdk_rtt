#include <stdint.h>
#ifndef __AUDIO_PUB_H__
#define __AUDIO_PUB_H__

#define AUD_FAILURE                  (1)
#define AUD_SUCCESS                  (0)

enum CODEC_STATE
{
    DAC_DMA_IRQ_ENABLE = 0x01,
    ADC_DMA_IRQ_ENABLE = 0x02,
    DAC_IRQ_ENABLE     = 0x04,
    ADC_IRQ_ENABLE     = 0x08,
    DAC_IS_OPENED      = 0x10,    
    ADC_IS_OPENED      = 0x40,    
};

#define AUD_DAC_DEV_NAME             "aud_dac"
#define AUD_DAC_CMD_MAGIC            (0x1EBC0000)

typedef struct aud_dac_cfg_st
{
    uint8_t *buf;
    uint16_t buf_len;
    uint16_t freq;
    uint16_t channels;
    uint16_t dma_mode;
    uint16_t mute_pin;
    uint16_t def_volume;
    #if CFG_GENERAL_DMA
    void (*buf_finish_cb)(uint8_t *buf, void *usr_data);
    void *usr_data;
    #endif
    
} AUD_DAC_CFG_ST, *AUD_DAC_CFG_PTR;

enum
{
    AUD_DAC_CMD_GET_FREE_BUF_SIZE = AUD_DAC_CMD_MAGIC + 1,
    AUD_DAC_CMD_PLAY,
    AUD_DAC_CMD_PAUSE,
    AUD_DAC_CMD_SET_SAMPLE_RATE,
    AUD_DAC_CMD_SET_VOLUME,    
};

#define AUD_DAC_VOL_TABLE_LEN       (17)
#define AUD_USE_EXT_PA              1
#include "gpio_pub.h"
#if AUD_USE_EXT_PA
#define AUD_DAC_MUTE_PIN            GPIO9
#define AUD_DAC_MUTE_ENA_LEVEL      GPIO_INT_LEVEL_LOW

/*adjust  delay according to different PA*/
#define PA_MUTE_DELAY 20
#define PA_UNMUTE_DELAY 50

#endif

#define AUD_DAC_SINGLE_PORT         1
#define AUD_DAC_DIFF_PORT           2
#define AUD_DAC_USE_PORT_SET        AUD_DAC_SINGLE_PORT


///////////////////////////////////////////////////////////////////////////////


#define AUD_ADC_DEV_NAME             "aud_adc"
#define AUD_ADC_CMD_MAGIC            (0x2EBC0000)
typedef struct aud_adc_cfg_st
{
    uint8_t *buf;
    uint16_t buf_len;
    uint16_t freq;
    uint16_t channels;
    uint16_t mode;
    uint32_t linein_detect_pin;
} AUD_ADC_CFG_ST, *AUD_ADC_CFG_PTR;

enum
{
    AUD_ADC_CMD_GET_FILL_BUF_SIZE = AUD_ADC_CMD_MAGIC + 1,
    AUD_ADC_CMD_PLAY,
    AUD_ADC_CMD_PAUSE,
    AUD_ADC_CMD_DO_LINEIN_DETECT,
    AUD_ADC_CMD_SET_SAMPLE_RATE,
    AUD_ADC_CMD_SET_VOLUME
};


#define AUD_ADC_LINEIN_DETECT_PIN           GPIO8
#define AUD_ADC_LINEIN_ENABLE_LEVEL         0
#define AUD_ADC_DAC_HARDWARD_LOOPBACK       0

#define AUD_ADC_MODE_DMA_BIT                (1 << 0)  // 1: DMA MODE, 0: ISR MODE
#define AUD_ADC_MODE_LINEIN                 (1 << 1)  // 1: LINEIN, 0: MIC 
#define AUD_ADC_DEF_WR_THRED                (8)
#define AUD_ADC_DEF_GAIN                    (0x2D)   // 0dm
#define AUD_ADC_MAX_THRED                   (0x10)
#define AUD_ADC_MAX_VOLUME                  (124)

void audio_adc_set_enable_bit(uint32_t enable);
void audio_adc_set_int_enable_bit(uint32_t enable);
void audio_adc_get_l_sample(int16_t *left);
void audio_adc_get_l_and_r_samples(int16_t *left, int16_t *right);
void audio_adc_set_hpf2_bypass_bit(uint32_t enable);
void audio_adc_set_gain(uint32_t gain);
void audio_adc_set_write_thred_bit(uint32_t thred);
void audio_adc_set_sample_rate(uint32_t sample_rate);
void audio_adc_set_dma(uint32_t enable);
void audio_adc_set_volume(uint32_t volume);

/* DAC Interface */
void audio_dac_set_enable_bit(uint32_t enable);
void audio_dac_set_int_enable_bit(uint32_t enable);
void audio_dac_set_read_thred_bit(uint32_t thred);
void audio_dac_set_gain(uint32_t gain);
void audio_dac_set_hpf1_bit(uint32_t enable);
void audio_dac_set_hpf2_bit(uint32_t enable);
void audio_dac_set_sample_rate(uint32_t sample_rate);
void audio_dac_set_sample(int16_t left, int16_t right);
void audio_dac_open_analog_regs(void);
void audio_dac_close_analog_regs(void);
void audio_dac_set_analog_mute(uint32_t enable);
void audio_dac_init_mute_pin(void);
void audio_dac_eable_mute(uint32_t enable);
uint32_t audio_dac_is_mute(void);
void audio_dac_set_volume(uint32_t percent);
void audio_dac_volume_use_single_port(void);
void audio_dac_volume_diff_port(void);

/* ADC Interface */
void audio_adc_open_analog_regs(void);
void audio_adc_close_analog_regs(void);

void audio_init(void);
void audio_exit(void);

#endif // __AUDIO_PUB_H__