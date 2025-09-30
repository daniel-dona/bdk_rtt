#include <stdint.h>
/*
 * hostapd / DPP integration
 * Copyright (c) 2017, Qualcomm Atheros, Inc.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef DPP_HOSTAPD_H
#define DPP_HOSTAPD_H

int hostapd_dpp_qr_code(struct hostapd_data *hapd, const char *cmd);
int hostapd_dpp_auth_init(struct hostapd_data *hapd, const char *cmd);
int hostapd_dpp_listen(struct hostapd_data *hapd, const char *cmd);
void hostapd_dpp_listen_stop(struct hostapd_data *hapd);
void hostapd_dpp_rx_action(struct hostapd_data *hapd, const uint8_t *src,
			   const uint8_t *buf, size_t len, unsigned int freq);
void hostapd_dpp_tx_status(struct hostapd_data *hapd, const uint8_t *dst,
			   const uint8_t *data, size_t data_len, int ok);
struct wpabuf *
hostapd_dpp_gas_req_handler(struct hostapd_data *hapd, const uint8_t *sa,
			    const uint8_t *query, size_t query_len,
			    const uint8_t *data, size_t data_len);
void hostapd_dpp_gas_status_handler(struct hostapd_data *hapd, int ok);
int hostapd_dpp_configurator_add(struct hostapd_data *hapd, const char *cmd);
int hostapd_dpp_configurator_remove(struct hostapd_data *hapd, const char *id);
int hostapd_dpp_configurator_sign(struct hostapd_data *hapd, const char *cmd);
int hostapd_dpp_configurator_get_key(struct hostapd_data *hapd, unsigned int id,
				     char *buf, size_t buflen);
int hostapd_dpp_pkex_add(struct hostapd_data *hapd, const char *cmd);
int hostapd_dpp_pkex_remove(struct hostapd_data *hapd, const char *id);
void hostapd_dpp_stop(struct hostapd_data *hapd);
int hostapd_dpp_init(struct hostapd_data *hapd);
void hostapd_dpp_deinit(struct hostapd_data *hapd);
void hostapd_dpp_init_global(struct hapd_interfaces *ifaces);
void hostapd_dpp_deinit_global(struct hapd_interfaces *ifaces);

#endif /* DPP_HOSTAPD_H */
