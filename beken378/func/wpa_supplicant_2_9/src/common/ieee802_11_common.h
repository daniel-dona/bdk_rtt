#include <stdint.h>
/*
 * IEEE 802.11 Common routines
 * Copyright (c) 2002-2019, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef IEEE802_11_COMMON_H
#define IEEE802_11_COMMON_H

#include "defs.h"
#include "ieee802_11_defs.h"

struct element {
	uint8_t id;
	uint8_t datalen;
	uint8_t data[];
} STRUCT_PACKED;

struct hostapd_hw_modes;

#define MAX_NOF_MB_IES_SUPPORTED 5

struct mb_ies_info {
	struct {
		const uint8_t *ie;
		uint8_t ie_len;
	} ies[MAX_NOF_MB_IES_SUPPORTED];
	uint8_t nof_ies;
};

/* Parsed Information Elements */
struct ieee802_11_elems {
	const uint8_t *ssid;
	const uint8_t *supp_rates;
	const uint8_t *ds_params;
	const uint8_t *challenge;
	const uint8_t *erp_info;
	const uint8_t *ext_supp_rates;
	const uint8_t *wpa_ie;
	const uint8_t *rsn_ie;
	const uint8_t *wmm; /* WMM Information or Parameter Element */
	const uint8_t *wmm_tspec;
	const uint8_t *wps_ie;
	const uint8_t *supp_channels;
	const uint8_t *mdie;
	const uint8_t *ftie;
	const uint8_t *timeout_int;
	const uint8_t *ht_capabilities;
	const uint8_t *ht_operation;
	const uint8_t *mesh_config;
	const uint8_t *mesh_id;
	const uint8_t *peer_mgmt;
	const uint8_t *vht_capabilities;
	const uint8_t *vht_operation;
	const uint8_t *vht_opmode_notif;
	const uint8_t *vendor_ht_cap;
	const uint8_t *vendor_vht;
	const uint8_t *p2p;
	const uint8_t *wfd;
	const uint8_t *link_id;
	const uint8_t *interworking;
	const uint8_t *qos_map_set;
	const uint8_t *hs20;
	const uint8_t *ext_capab;
	const uint8_t *bss_max_idle_period;
	const uint8_t *ssid_list;
	const uint8_t *osen;
	const uint8_t *mbo;
	const uint8_t *ampe;
	const uint8_t *mic;
	const uint8_t *pref_freq_list;
	const uint8_t *supp_op_classes;
	const uint8_t *rrm_enabled;
	const uint8_t *cag_number;
	const uint8_t *ap_csn;
	const uint8_t *fils_indic;
	const uint8_t *dils;
	const uint8_t *assoc_delay_info;
	const uint8_t *fils_req_params;
	const uint8_t *fils_key_confirm;
	const uint8_t *fils_session;
	const uint8_t *fils_hlp;
	const uint8_t *fils_ip_addr_assign;
	const uint8_t *key_delivery;
	const uint8_t *fils_wrapped_data;
	const uint8_t *fils_pk;
	const uint8_t *fils_nonce;
	const uint8_t *owe_dh;
	const uint8_t *power_capab;
	const uint8_t *roaming_cons_sel;
	const uint8_t *password_id;
	const uint8_t *oci;
	const uint8_t *multi_ap;
	const uint8_t *he_capabilities;
	const uint8_t *he_operation;

	uint8_t ssid_len;
	uint8_t supp_rates_len;
	uint8_t challenge_len;
	uint8_t ext_supp_rates_len;
	uint8_t wpa_ie_len;
	uint8_t rsn_ie_len;
	uint8_t wmm_len; /* 7 = WMM Information; 24 = WMM Parameter */
	uint8_t wmm_tspec_len;
	uint8_t wps_ie_len;
	uint8_t supp_channels_len;
	uint8_t mdie_len;
	uint8_t ftie_len;
	uint8_t mesh_config_len;
	uint8_t mesh_id_len;
	uint8_t peer_mgmt_len;
	uint8_t vendor_ht_cap_len;
	uint8_t vendor_vht_len;
	uint8_t p2p_len;
	uint8_t wfd_len;
	uint8_t interworking_len;
	uint8_t qos_map_set_len;
	uint8_t hs20_len;
	uint8_t ext_capab_len;
	uint8_t ssid_list_len;
	uint8_t osen_len;
	uint8_t mbo_len;
	uint8_t ampe_len;
	uint8_t mic_len;
	uint8_t pref_freq_list_len;
	uint8_t supp_op_classes_len;
	uint8_t rrm_enabled_len;
	uint8_t cag_number_len;
	uint8_t fils_indic_len;
	uint8_t dils_len;
	uint8_t fils_req_params_len;
	uint8_t fils_key_confirm_len;
	uint8_t fils_hlp_len;
	uint8_t fils_ip_addr_assign_len;
	uint8_t key_delivery_len;
	uint8_t fils_wrapped_data_len;
	uint8_t fils_pk_len;
	uint8_t owe_dh_len;
	uint8_t power_capab_len;
	uint8_t roaming_cons_sel_len;
	uint8_t password_id_len;
	uint8_t oci_len;
	uint8_t multi_ap_len;
	uint8_t he_capabilities_len;
	uint8_t he_operation_len;

	struct mb_ies_info mb_ies;
};

typedef enum { ParseOK = 0, ParseUnknown = 1, ParseFailed = -1 } ParseRes;

ParseRes ieee802_11_parse_elems(const uint8_t *start, size_t len,
				struct ieee802_11_elems *elems,
				int show_errors);
int ieee802_11_ie_count(const uint8_t *ies, size_t ies_len);
struct wpabuf * ieee802_11_vendor_ie_concat(const uint8_t *ies, size_t ies_len,
					    uint32_t oui_type);
struct ieee80211_hdr;
const uint8_t * get_hdr_bssid(const struct ieee80211_hdr *hdr, size_t len);

struct hostapd_wmm_ac_params {
	int cwmin;
	int cwmax;
	int aifs;
	int txop_limit; /* in units of 32us */
	int admission_control_mandatory;
};

int hostapd_config_wmm_ac(struct hostapd_wmm_ac_params wmm_ac_params[],
			  const char *name, const char *val);
enum hostapd_hw_mode ieee80211_freq_to_chan(int freq, uint8_t *channel);
int ieee80211_chan_to_freq(const char *country, uint8_t op_class, uint8_t chan);
enum hostapd_hw_mode ieee80211_freq_to_channel_ext(unsigned int freq,
						   int sec_channel, int vht,
						   uint8_t *op_class, uint8_t *channel);
int ieee80211_chaninfo_to_channel(unsigned int freq, enum chan_width chanwidth,
				  int sec_channel, uint8_t *op_class, uint8_t *channel);
int ieee80211_is_dfs(int freq, const struct hostapd_hw_modes *modes,
		     uint16_t num_modes);
enum phy_type ieee80211_get_phy_type(int freq, int ht, int vht);

int supp_rates_11b_only(struct ieee802_11_elems *elems);
int mb_ies_info_by_ies(struct mb_ies_info *info, const uint8_t *ies_buf,
		       size_t ies_len);
struct wpabuf * mb_ies_by_info(struct mb_ies_info *info);

const char * fc2str(uint16_t fc);
const char * reason2str(uint16_t reason);
const char * status2str(uint16_t status);

struct oper_class_map {
	enum hostapd_hw_mode mode;
	uint8_t op_class;
	uint8_t min_chan;
	uint8_t max_chan;
	uint8_t inc;
	enum { BW20, BW40PLUS, BW40MINUS, BW80, BW2160, BW160, BW80P80 } bw;
	enum { P2P_SUPP, NO_P2P_SUPP } p2p;
};

extern const struct oper_class_map global_op_class[];
extern size_t global_op_class_size;

const uint8_t * get_ie(const uint8_t *ies, size_t len, uint8_t eid);
const uint8_t * get_ie_ext(const uint8_t *ies, size_t len, uint8_t ext);
const uint8_t * get_vendor_ie(const uint8_t *ies, size_t len, uint32_t vendor_type);

size_t mbo_add_ie(uint8_t *buf, size_t len, const uint8_t *attr, size_t attr_len);

size_t add_multi_ap_ie(uint8_t *buf, size_t len, uint8_t value);

struct country_op_class {
	uint8_t country_op_class;
	uint8_t global_op_class;
};

uint8_t country_to_global_op_class(const char *country, uint8_t op_class);

const struct oper_class_map * get_oper_class(const char *country, uint8_t op_class);
int oper_class_bw_to_int(const struct oper_class_map *map);

int ieee802_11_parse_candidate_list(const char *pos, uint8_t *nei_rep,
				    size_t nei_rep_len);

int ieee802_11_ext_capab(const uint8_t *ie, unsigned int capab);

/* element iteration helpers */
#define for_each_element(_elem, _data, _datalen)			\
	for (_elem = (const struct element *) (_data);			\
	     (const uint8_t *) (_data) + (_datalen) - (const uint8_t *) _elem >=	\
		(int) sizeof(*_elem) &&					\
	     (const uint8_t *) (_data) + (_datalen) - (const uint8_t *) _elem >=	\
		(int) sizeof(*_elem) + _elem->datalen;			\
	     _elem = (const struct element *) (_elem->data + _elem->datalen))

#define for_each_element_id(element, _id, data, datalen)		\
	for_each_element(element, data, datalen)			\
		if (element->id == (_id))

#define for_each_element_extid(element, extid, _data, _datalen)		\
	for_each_element(element, _data, _datalen)			\
		if (element->id == WLAN_EID_EXTENSION &&		\
		    element->datalen > 0 &&				\
		    element->data[0] == (extid))

#define for_each_subelement(sub, element)				\
	for_each_element(sub, (element)->data, (element)->datalen)

#define for_each_subelement_id(sub, id, element)			\
	for_each_element_id(sub, id, (element)->data, (element)->datalen)

#define for_each_subelement_extid(sub, extid, element)			\
	for_each_element_extid(sub, extid, (element)->data, (element)->datalen)

/**
 * for_each_element_completed - Determine if element parsing consumed all data
 * @element: Element pointer after for_each_element() or friends
 * @data: Same data pointer as passed to for_each_element() or friends
 * @datalen: Same data length as passed to for_each_element() or friends
 *
 * This function returns 1 if all the data was parsed or considered
 * while walking the elements. Only use this if your for_each_element()
 * loop cannot be broken out of, otherwise it always returns 0.
 *
 * If some data was malformed, this returns %false since the last parsed
 * element will not fill the whole remaining data.
 */
static inline int for_each_element_completed(const struct element *element,
					     const void *data, size_t datalen)
{
	return (const uint8_t *) element == (const uint8_t *) data + datalen;
}

#endif /* IEEE802_11_COMMON_H */
