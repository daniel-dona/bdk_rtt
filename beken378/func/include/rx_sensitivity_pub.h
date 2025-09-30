#include <stdint.h>
#ifndef _RX_SENSITIVITY_H_
#define _RX_SENSITIVITY_H_

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern void rs_test(void);
extern void rx_get_rx_result_begin(void);
extern void rx_get_rx_result_end(void);
extern uint32_t rs_set_channel(uint32_t channel_id);
extern uint32_t rs_set_mode(uint32_t mode);

extern void rx_clean_rx_statistic_result(void);
extern uint32_t rx_get_rx20M_statistic_result(void);
extern uint32_t rx_get_rx40M_statistic_result(void);

extern void rx_clean_ble_rx_result(void);
extern void rx_start_ble_rx_counting();
extern void rs_ble_test_start(uint32_t channel);
extern void rs_ble_test_stop(void);
extern void rx_get_ble_rx_result(void);


#endif //_RX_SENSITIVITY_H_
// eof

