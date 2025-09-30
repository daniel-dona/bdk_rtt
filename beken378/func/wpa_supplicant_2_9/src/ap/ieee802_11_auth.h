#include <stdint.h>
/*
 * hostapd / IEEE 802.11 authentication (ACL)
 * Copyright (c) 2003-2005, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef IEEE802_11_AUTH_H
#define IEEE802_11_AUTH_H

enum {
	HOSTAPD_ACL_REJECT = 0,
	HOSTAPD_ACL_ACCEPT = 1,
	HOSTAPD_ACL_PENDING = 2,
	HOSTAPD_ACL_ACCEPT_TIMEOUT = 3
};

int hostapd_check_acl(struct hostapd_data *hapd, const uint8_t *addr,
		      struct vlan_description *vlan_id);
int hostapd_allowed_address(struct hostapd_data *hapd, const uint8_t *addr,
			    const uint8_t *msg, size_t len, uint32_t *session_timeout,
			    uint32_t *acct_interim_interval,
			    struct vlan_description *vlan_id,
			    struct hostapd_sta_wpa_psk_short **psk,
			    char **identity, char **radius_cui,
			    int is_probe_req);
int hostapd_acl_init(struct hostapd_data *hapd);
void hostapd_acl_deinit(struct hostapd_data *hapd);
void hostapd_free_psk_list(struct hostapd_sta_wpa_psk_short *psk);
void hostapd_acl_expire(struct hostapd_data *hapd);

#endif /* IEEE802_11_AUTH_H */
