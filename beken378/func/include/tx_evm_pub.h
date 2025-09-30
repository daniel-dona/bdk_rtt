#include <stdint.h>
#ifndef _TX_EVM_PUB_H_
#define _TX_EVM_PUB_H_

#include "hal_desc.h"

#define TX_LEGACY_MODE              (1)
#define TX_HT_VHT_MODE              (2)

#define TX_LEGACY_DATA_LEN_MASK              (0xFFF)
#define TX_HT_VHT_DATA_LEN_MASK              (0xFFFFF)

typedef enum
{
    SINGLE_CARRIER_11B,
    SINGLE_CARRIER_11G,
    SINGLE_CARRIER_BLE
} SC_TYPE_T;

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern void evm_via_mac_evt(int32_t dummy);
extern void evm_via_mac_begin(void);
extern void evm_via_mac_continue(void);
extern uint32_t evm_bypass_mac_set_tx_data_length(uint32_t modul_format, uint32_t len, uint32_t rate, uint32_t bandwidth, uint32_t need_change);
extern uint32_t evm_bypass_mac_set_rate_mformat(uint32_t ppdu_rate, uint32_t m_format);
extern void evm_bypass_mac_set_channel(uint32_t channel);
extern void evm_via_mac_set_channel(uint32_t channel);
extern void evm_bypass_mac_test(void);
extern void evm_via_mac_set_rate(HW_RATE_E rate, uint32_t modul_format, uint32_t guard_i_tpye);
extern void evm_set_bandwidth(uint32_t bandwidth);
extern void evm_stop_bypass_mac(void);
extern void evm_bypass_mac_set_guard_i_type(uint32_t gi_tpye);
extern void evm_start_bypass_mac(void);
extern void evm_bypass_set_single_carrier(SC_TYPE_T type, uint32_t rate);
extern void evm_bypass_ble_test_start(uint32_t channel);
extern void evm_bypass_ble_test_stop(void);
extern void evm_via_mac_init(void);
extern void evm_via_mac_set_power(uint32_t pwr_idx);
extern void evm_via_mac_set_bandwidth(uint32_t bandwidth);
extern uint32_t evm_bypass_mac_set_txdelay(uint32_t delay_us);

#endif //_TX_EVM_PUB_H_
// eof

