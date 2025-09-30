#include <stdint.h>
#ifndef _SARADC_PUB_H_
#define _SARADC_PUB_H_

#define SARADC_FAILURE                (1)
#define SARADC_SUCCESS                (0)

#define SARADC_DEV_NAME                "saradc"

#define SARADC_CMD_MAGIC              (0xe290000)
enum
{
    SARADC_CMD_SET_MODE = SARADC_CMD_MAGIC + 1,
    SARADC_CMD_SET_CHANNEL,
    SARADC_CMD_SET_SAMPLE_RATE,
    SARADC_CMD_SET_WAITING_TIME,
    SARADC_CMD_SET_VALID_MODE,
    SARADC_CMD_CLEAR_INT,
    SARADC_CMD_SET_CLK_RATE,
    SARADC_CMD_RUN_OR_STOP_ADC,
    SARADC_CMD_SET_CAL_VAL,
    SARADC_CMD_SET_BYPASS_CALIB,
    SARADC_CMD_PAUSE,
    SARADC_CMD_RESUME,
};

typedef enum
{
    SARADC_CALIBRATE_LOW,
    SARADC_CALIBRATE_HIGH
} SARADC_MODE;

#define ADC_CONFIG_MODE_SLEEP           (0x00UL)
#define ADC_CONFIG_MODE_STEP            (0x01UL)
#define ADC_CONFIG_MODE_SOFT_CTRL       (0x02UL)
#define ADC_CONFIG_MODE_CONTINUE        (0x03UL)

#define ADC_CONFIG_MODE_4CLK_DELAY      (0x0UL)
#define ADC_CONFIG_MODE_8CLK_DELAY      (0x1UL)
#define ADC_CONFIG_MODE_SHOULD_OFF      (1 << 3)

typedef struct
{
    uint16_t *pData;
    volatile uint8_t current_sample_data_cnt;
    volatile uint8_t current_read_data_cnt;
    uint8_t data_buff_size;
    volatile uint8_t has_data; /* 1: has data      0: no data*/
    volatile uint8_t all_done; /* 1: all done      0: still sampling*/
    uint8_t channel;
    /* mode:     ADC mode
     * bit[0:1]: ADC operation mode
     *          00:  ADC power down mode
     *          01:  ADC one-step mode
     *          10:  ADC software control mode
     *          11:  ADC continuous mode
     * bit[2:2]: delay clk(adc setting)
     *           0: delay 4 clk
     *           1: delay 8 clk
     * bit[7:3]: reserved
     */
    uint8_t mode;
    void (*p_Int_Handler)(void);
    unsigned char pre_div;					// ADC pre-divide clk
    unsigned char samp_rate;				// ADC sample rate
    unsigned char filter;                   //ADC filter
} saradc_desc_t;

typedef struct
{
    uint8_t enable;
    uint8_t channel;
} saradc_chan_t;

typedef struct 
{
    unsigned short val;
    SARADC_MODE mode;
} saradc_cal_val_t;

typedef struct _saradc_calibrate_val_
{
    unsigned short low;
    unsigned short high;
} saradc_calibrate_val;


/*******************************************************************************
* Function Declarations
*******************************************************************************/
void saradc_disable(void);
void saradc_init(void);
void saradc_exit(void);
void saradc_isr(void);
float saradc_calculate(uint16_t adc_val);
void saradc_config_param_init(saradc_desc_t * adc_config);
void saradc_ensure_close(void);
uint32_t saradc_check_busy(void);
uint32_t saradc_check_accuracy(void);

extern saradc_calibrate_val saradc_val;
#endif //_SARADC_PUB_H_
