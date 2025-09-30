#include <stdint.h>
#ifndef _SA_STATION_H_
#define _SA_STATION_H_

#include "includes.h"
#include "schedule_pub.h"
#include "rw_msg_tx.h"

#define SASTA_DEBUG

#ifdef SASTA_DEBUG
#define SASTA_PRT                 os_printf
#define SASTA_WPRT                warning_prf
#else
#define SASTA_PRT                 os_null_printf
#define SASTA_WPRT                os_null_printf
#endif

#define SCANU_IND_PAYLOAD_LEN                   512

typedef struct _scan_result_
{
    /// Length of the frame
    uint16_t length;
    /// Frame control field of the frame.
    uint16_t framectrl;
    /// Center frequency on which we received the packet
    uint16_t center_freq;
    /// PHY band
    uint8_t band;
    /// Index of the station that sent the frame. 0xFF if unknown.
    uint8_t sta_idx;
    /// Index of the VIF that received the frame. 0xFF if unknown.
    uint8_t inst_nbr;
    /// RSSI of the received frame.
    int8_t rssi;
    /// Frame payload.
    uint32_t payload[1];
} SCAN_IND_T, *SCAN_IND_PTR;

typedef struct probe_rsp
{
    uint8_t timestamp[8];
    uint16_t beacon_int;
    uint16_t capab_info;

    /* followed by some of SSID, Supported rates,
     * FH Params, DS Params, CF Params, IBSS Params */
    uint8_t variable[1];
} __attribute__ ((packed)) PROBE_RSP_T;

typedef struct ieee802_11_probe_rsp
{
    uint16_t frame_control;
    uint16_t duration;
    uint8_t da[6];
    uint8_t sa[6];
    uint8_t bssid[6];
    uint16_t seq_ctrl;
    struct probe_rsp rsp;
} __attribute__ ((packed)) IEEE802_11_PROBE_RSP_T, *IEEE802_11_PROBE_RSP_PTR;

void sa_station_init(void);
void sa_station_uninit(void);
void sa_station_set_reconnect_timer(void);
void sa_reconnect_init(void);
#ifdef CONFIG_SME
int sa_station_send_associate_cmd(ASSOC_PARAM_T *assoc_param);
#else
int sa_station_send_associate_cmd(CONNECT_PARAM_T *connect_param);
#endif

#endif // _SA_STATION_H_
// eof

