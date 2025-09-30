#include <stdint.h>
/*
 * wpa_supplicant - Temporary BSSID blacklist
 * Copyright (c) 2003-2007, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef BLACKLIST_H
#define BLACKLIST_H

struct wpa_blacklist {
	struct wpa_blacklist *next;
	uint8_t bssid[ETH_ALEN];
	int count;
};

struct wpa_blacklist * wpa_blacklist_get(struct wpa_supplicant *wpa_s,
					 const uint8_t *bssid);
int wpa_blacklist_add(struct wpa_supplicant *wpa_s, const uint8_t *bssid);
int wpa_blacklist_del(struct wpa_supplicant *wpa_s, const uint8_t *bssid);
void wpa_blacklist_clear(struct wpa_supplicant *wpa_s);

#endif /* BLACKLIST_H */
