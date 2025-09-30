#include <stdint.h>
/*
 * hostapd - WPA/RSN IE and KDE definitions
 * Copyright (c) 2004-2007, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef WPA_AUTH_IE_H
#define WPA_AUTH_IE_H

struct wpa_eapol_ie_parse {
	const uint8_t *wpa_ie;
	size_t wpa_ie_len;
	const uint8_t *rsn_ie;
	size_t rsn_ie_len;
	const uint8_t *pmkid;
	const uint8_t *gtk;
	size_t gtk_len;
	const uint8_t *mac_addr;
	size_t mac_addr_len;
#ifdef CONFIG_IEEE80211W_AP
	const uint8_t *igtk;
	size_t igtk_len;
#endif /* CONFIG_IEEE80211W_AP */
#ifdef CONFIG_IEEE80211R_AP
	const uint8_t *mdie;
	size_t mdie_len;
	const uint8_t *ftie;
	size_t ftie_len;
#endif /* CONFIG_IEEE80211R_AP */
#ifdef CONFIG_P2P
	const uint8_t *ip_addr_req;
	const uint8_t *ip_addr_alloc;
#endif /* CONFIG_P2P */
#ifdef CONFIG_OCV
	const uint8_t *oci;
	size_t oci_len;
#endif /* CONFIG_OCV */

	const uint8_t *osen;
	size_t osen_len;
};

int wpa_parse_kde_ies(const uint8_t *buf, size_t len,
		      struct wpa_eapol_ie_parse *ie);
uint8_t * wpa_add_kde(uint8_t *pos, uint32_t kde, const uint8_t *data, size_t data_len,
		 const uint8_t *data2, size_t data2_len);
int wpa_auth_gen_wpa_ie(struct wpa_authenticator *wpa_auth);

#endif /* WPA_AUTH_IE_H */
