#include <stdint.h>
#ifndef _BK7011_CAL_PUB_H_
#define _BK7011_CAL_PUB_H_

#include "typedef.h"
#include "sys_config.h"
#define BK_FLASH_OPT_TLV_HEADER           (0x00564c54)   // ASIC TLV
typedef enum{
    TXID                        = 0x11111100,
    TXPWR_TAB_TAB               = 0x22222200,
    CALI_MAIN_TX                = 0x33333300,
    CALI_MAIN_RX                = 0x44444400,
    TXEND                       = 0xeeeeeeee,
    TXNON                       = 0xffffffff
}TXSTRUCT;

#define DEFAULT_TXID_ID           (12345678)
#if (CFG_SOC_NAME == SOC_BK7231N)
#define DEFAULT_TXID_THERMAL      (350)
#else
#define DEFAULT_TXID_THERMAL      (280) //180430,7231:315,7231U:340
#endif
#define DEFAULT_TXID_CHANNEL      (22222222)
#define DEFAULT_TXID_LPF_CAP_I    (0x80)
#define DEFAULT_TXID_LPF_CAP_Q    (0x80)
typedef enum{
    TXID_ID                     = TXID+1,
    TXID_MAC,
    TXID_THERMAL,
    TXID_CHANNEL,
    TXID_XTAL,
    TXID_ADC,    
    TXID_LPFCAP,
    TXID_END,
    TXID_NON                    = TXID+0xFF
}TXIDList;

typedef enum{
    TXPWR_ENABLE_ID             = TXPWR_TAB_TAB+1,
    TXPWR_TAB_B_ID,
    TXPWR_TAB_G_ID,
    TXPWR_TAB_N_ID,
    TXPWR_TAB_DIF_GN20_ID,
    TXPWR_TAB_DIF_GN40_ID,
    TXPWR_TAB_BLE_ID,
    TXPWR_TAB_CALI_STATUTS,
    TXPWR_END,
    TXPWR_NON                   = TXPWR_TAB_TAB+0xFF
}TXPWR_ELEM_ID;

typedef enum {
    TXPWR_NONE_RD               = 0u,
    TXPWR_TAB_B_RD              = 0x1u,
    TXPWR_TAB_G_RD              = 0x2u,
    TXPWR_TAB_N_RD              = 0x4u,
    TXPWR_TAB_BLE               = 0x8u,
} TXPWR_IS_RD;

typedef enum{
    CM_TX_DCOR_MOD              = CALI_MAIN_TX+1,
    CM_TX_DCOR_PA,
    CM_TX_PREGAIN,
    CM_TX_I_DC_COMP,
    CM_TX_Q_DC_COMP,
    CM_TX_I_GAIN_COMP,
    CM_TX_Q_GAIN_COMP,
    CM_TX_I_FILTER_CORNER,
    CM_TX_Q_FILTER_CORNER,
    CM_TX_PHASE_COMP,
    CM_TX_PHASE_TY2,
    CM_TX_END,
    CM_TX_NON                   = CALI_MAIN_TX+0xFF
}CM_TX_ELEM_ID;

typedef enum{
    CM_RX_DC_GAIN_TAB           = CALI_MAIN_RX+1,
    CM_RX_AMP_ERR_WR,
    CM_RX_PHASE_ERR_WR,
    CM_RX_END,
    CM_RX_NON                   = CALI_MAIN_RX+0xFF
}CM_RX_ELEM_ID;

#define LOAD_FROM_FLASH         1
#define LOAD_FROM_CALI          0
#define CALI_MODE_AUTO          0
#define CALI_MODE_MANUAL        1
#define CALI_STATUS_PASS        1
#define CALI_STATUS_FAIL        0

#if (CFG_SOC_NAME == SOC_BK7231N)
typedef struct tmp_pwr_st {//do
    unsigned trx0x0c_12_15 : 4; //not used on BK7231N actually
    signed p_index_delta : 6;
    signed p_index_delta_g : 6;
    signed p_index_delta_ble : 6;
    signed xtal_c_dlta : 8;
} TMP_PWR_ST, *TMP_PWR_PTR;
#elif (CFG_SOC_NAME != SOC_BK7231)
typedef struct tmp_pwr_st {
    unsigned trx0x0c_12_15 : 4;
    signed p_index_delta : 6;
    signed p_index_delta_g : 6;
    signed p_index_delta_ble : 6;
    unsigned xtal_c_dlta : 6; 
} TMP_PWR_ST, *TMP_PWR_PTR;
#else
typedef struct tmp_pwr_st {
    uint8_t mod;
    uint8_t pa;
	uint16_t pwr_idx_shift;
} TMP_PWR_ST, *TMP_PWR_PTR;
#endif

struct temp_cal_pwr_st {
    uint8_t idx;
    uint8_t mode;
    int16_t shift;
    int16_t shift_g;
    int16_t shift_ble;
};

typedef enum
{
    TEMPERATURE_TYPE_UNKNOWN = 0,
    TEMPERATURE_TYPE_LOW,
    TEMPERATURE_TYPE_NORMAL,
    TEMPERATURE_TYPE_HIGH,
} temperature_type;


extern void manual_cal_load_bandgap_calm(void);
void bk7011_cal_vdddig_by_temperature(temperature_type new_temperature_type);

extern void calibration_main(void);
extern int32_t rwnx_cal_load_trx_rcbekn_reg_val(void);
extern void rwnx_cal_set_txpwr_by_rate(int32_t rate, uint32_t test_mode);
extern void rwnx_cal_set_txpwr_by_channel(uint32_t channel);
extern int32_t rwnx_cal_save_trx_rcbekn_reg_val(void);
extern void do_calibration_in_temp_dect(void);
extern void bk7011_cal_bias(void);
extern void bk7011_cal_bias_low_temprature(uint8_t low_temprature);
extern void bk7011_cal_bias_high_temprature(uint8_t high_temprature);
extern void bk7011_cal_dpll(void);
extern void rwnx_cal_set_txpwr(uint32_t pwr_gain, uint32_t grate);
extern uint32_t manual_cal_get_pwr_idx_shift(uint32_t rate, uint32_t bandwidth, uint32_t *pwr_gain);
extern int manual_cal_get_txpwr(uint32_t rate, uint32_t channel, uint32_t bandwidth, uint32_t *pwr_gain);
extern void manual_cal_save_txpwr(uint32_t rate, uint32_t channel, uint32_t pwr_gain);
#if (CFG_SOC_NAME != SOC_BK7231)
extern void manual_cal_11b_2_ble(void);
#endif
extern uint32_t manual_cal_fitting_txpwr_tab(void);
extern void manual_cal_show_txpwr_tab(void);
extern uint32_t manual_cal_load_txpwr_tab_flash(void);
extern int manual_cal_save_txpwr_tab_to_flash(void);
extern int manual_cal_save_chipinfo_tab_to_flash(void);
extern uint8_t manual_cal_wirte_otp_flash(uint32_t addr, uint32_t len, uint8_t *buf);
extern uint8_t manual_cal_read_otp_flash(uint32_t addr, uint32_t len, uint8_t *buf);
extern uint32_t manual_cal_load_default_txpwr_tab(uint32_t is_ready_flash);
extern void manual_cal_set_dif_g_n40(uint32_t diff);
extern void manual_cal_set_dif_g_n20(uint32_t diff);
extern void manual_cal_set_dif_g_ble(int dif_ch0, int dif_ch19, int dif_ch39);
extern void manual_cal_set_dif_ble(uint32_t diff);
extern void manual_cal_get_current_temperature(void);
extern int manual_cal_write_macaddr_to_flash(uint8_t *mac_ptr);
extern int manual_cal_get_macaddr_from_flash(uint8_t *mac_ptr);
extern int manual_cal_set_rfcali_status_inflash(uint32_t rf_status);
extern int manual_cal_get_rfcali_status_inflash(uint32_t *rf_status);
extern void manual_cal_show_otp_flash(void);
extern void manual_cal_clear_otp_flash(void);
extern void manual_cal_set_xtal(uint32_t xtal);
extern void manual_cal_set_lpf_iq(uint32_t lpf_i, uint32_t lpf_q);
extern void manual_cal_load_lpf_iq_tag_flash(void);
extern void manual_cal_load_xtal_tag_flash(void);
extern void manual_cal_do_xtal_temp_delta_set(int8_t shift);
extern void manual_cal_do_xtal_cali(uint16_t cur_val, uint16_t *last, uint16_t thre, uint16_t init_val);
extern uint32_t manual_cal_get_xtal(void);
extern int8_t manual_cal_get_dbm_by_rate(uint32_t rate, uint32_t bandwidth);
extern int8_t manual_cal_get_cur_txpwr_dbm(void);
extern int manual_cal_load_temp_tag_from_flash(void);
extern int manual_cal_load_xtal_tag_from_flash(void);
extern void manual_cal_load_differ_tag_from_flash(void);

extern void bk7011_micopwr_config_tssi_read_prepare(void);
extern void bk7011_micopwr_tssi_read(void);
extern void bk7011_micopwr_tssi_show(void);
extern void rwnx_cal_set_reg_adda_ldo(uint32_t val);
extern void rwnx_cal_set_reg_rx_ldo(void);

extern void manual_cal_tmp_pwr_init(uint16_t init_temp, uint16_t init_thre, uint16_t init_dist);
extern void manual_cal_tmp_pwr_init_reg(uint16_t reg_mod, uint16_t reg_pa);
extern void manual_cal_temp_pwr_unint(void);
extern void manual_cal_set_tmp_pwr_flag(uint8_t flag);
extern TMP_PWR_PTR manual_cal_set_tmp_pwr(uint16_t cur_val, uint16_t thre, uint16_t *last);
extern uint32_t manual_cal_load_temp_tag_flash(void);
extern uint32_t manual_cal_load_adc_cali_flash(void);
extern void manual_cal_do_single_temperature(void);
extern void manual_cal_set_rate_dist_for_txpwr(int dist_b, int dist_g, int dist_n40, int dist_ble);

extern void rwnx_cal_set_reg_mod_pa(uint16_t reg_mod, uint16_t reg_pa);
extern void rwnx_cal_do_temp_detect(uint16_t cur_val, uint16_t thre, uint16_t *last);
extern void rwnx_cal_set_lpfcap_iq(uint32_t lpfcap_i, uint32_t lpfcap_q);
extern void rwnx_cal_set_40M_extra_setting(uint8_t val);
extern void rwnx_cal_set_40M_setting(void);
extern void rwnx_cal_set_20M_setting(void);

extern void rwnx_cal_set_txpwr_for_ble_boardcast(void);
extern void bk7011_set_rf_config_tssithred_b(int tssi_thred_b);
extern void bk7011_set_rf_config_tssithred_g(int tssi_thred_g);
extern void rwnx_cal_recover_txpwr_for_wifi(void);
#if (CFG_SOC_NAME == SOC_BK7231N)
extern void rwnx_cal_recover_rf_setting(void);
extern void rwnx_cal_recover_wifi_setting(void);
#endif
extern void rwnx_cal_initial_calibration(void);

extern uint32_t rwnx_tpc_pwr_idx_translate(uint32_t pwr_gain, uint32_t rate, uint32_t print_log );
extern uint32_t rwnx_tpc_get_pwridx_by_rate(uint32_t rate, uint32_t print_log);
extern void rwnx_use_tpc_set_pwr(void);
extern void rwnx_no_use_tpc_set_pwr(void);
extern uint32_t rwnx_is_tpc_bit_on(void);
extern uint32_t rwnx_sys_is_enable_hw_tpc(void);
extern void bk7011_set_rf_config_tssithred(int tssi_thred);
extern int bk7011_is_rfcali_mode_auto(void);
extern void bk7011_set_rfcali_mode(int mode);
extern void bk7011_cal_dcormod_show(void);
extern void bk7011_get_tx_filter_corner(int32_t *tx_ifilter_corner, int32_t *tx_qfilter_corner);
extern void bk7011_get_tx_dc_comp(int32_t *tx_i_dc_comp, int32_t *tx_q_dc_comp);
extern void bk7011_get_tx_gain_comp(int32_t *tx_i_gain_comp, int32_t *tx_q_gain_comp);
extern void bk7011_get_tx_phase(int32_t *tx_phase_comp, int32_t *tx_phase_ty2);
extern void bk7011_get_rx_err_wr(int32_t *rx_amp_err_wr, int32_t *rx_phase_err_wr, int32_t *rx_dc_gain_tab);
extern void bk7011_get_tx_tssi_thred(int32_t *tx_tssi_thred_b, int32_t *tx_tssi_thred_g);

extern void rwnx_cal_ble_set_rfconfig(void);
extern void rwnx_cal_ble_recover_rfconfig(void);
extern void bk7011_set_rfcali_mode(int mode);
extern void manual_cal_set_setp0(void);
extern void manual_cal_set_setp1(void);
extern void manual_cal_clear_setp(void);
extern void manual_cal_set_rfcal_step0(void);
extern int manual_cal_rfcali_status(void);
extern int manual_cal_updata_rfcali_status(void);
extern uint32_t manual_cal_check_pwr_idx(uint32_t *level);
extern uint32_t manual_cal_is_in_rftest_mode(void);

extern void rwnx_cal_en_extra_txpa(void);
extern void rwnx_cal_dis_extra_txpa(void);

extern int manual_cal_save_cailmain_tx_tab_to_flash(void);
extern int manual_cal_save_cailmain_rx_tab_to_flash(void);
extern int manual_cal_load_calimain_tag_from_flash(uint32_t tag, int *tag_addr, int tag_size);
extern int manual_cal_need_load_cmtag_from_flash(void);
extern void manual_set_cmtag(uint32_t status);
extern void do_all_calibration(void);

extern uint32_t manual_cal_is_tlv_tag_in_flash(void);
extern uint32_t manual_cal_txpwr_tab_ready_in_flash(void);

extern uint32_t rwnx_cal_load_user_rfcali_mode(int *rfcali_mode) __attribute__ ((weak));
extern uint32_t rwnx_cal_load_user_g_tssi_threshold(int *tssi_g) __attribute__ ((weak));
extern uint32_t rwnx_cal_load_user_b_tssi_threshold(int *tssi_b) __attribute__ ((weak));
extern uint32_t rwnx_cal_is_auto_rfcali_printf_on(void) __attribute__ ((weak));

extern void cmd_rfcali_cfg_mode(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
extern void cmd_rfcali_cfg_rate_dist(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
extern void cmd_rfcali_cfg_tssi_g(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
extern void cmd_rfcali_cfg_tssi_b(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
extern void cmd_rfcali_show_data(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
#endif // _BK7011_CAL_PUB_H_
