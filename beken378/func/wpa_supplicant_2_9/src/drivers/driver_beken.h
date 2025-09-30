#include <stdint.h>
/*
 * Driver interaction with Linux Host AP driver
 * Copyright (c) 2002-2006, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef HOSTAP_DRIVER_H
#define HOSTAP_DRIVER_H

#include "ddrv.h"
#include "fake_socket.h"

typedef void * c_addr_t;

#define TMP_BUF_LEN    (512)

#define WLAN_RATE_1M      BIT(0)
#define WLAN_RATE_2M      BIT(1)
#define WLAN_RATE_5M5     BIT(2)
#define WLAN_RATE_11M     BIT(3)

#define IWEVGENIE       0x8C05  /* Generic IE (WPA, RSN, WMM, ..)
                                 * (scan results); This includes id and
                                 * length fields. One IWEVGENIE may
                                 * contain more than one IE. Scan
                                 * results may contain one or more
                                 * IWEVGENIE events. */
#define IWEVMICHAELMICFAILURE 0x8C06    /* Michael MIC failure
                                         * (struct iw_michaelmicfailure)
                                         */
#define IWEVASSOCREQIE  0x8C07  /* IEs used in (Re)Association Request.
                                 * The data includes id and length
                                 * fields and may contain more than one
                                 * IE. This event is required in
                                 * Managed mode if the driver
                                 * generates its own WPA/RSN IE. This
                                 * should be sent just before
                                 * IWEVREGISTERED event for the
                                 * association. */
#define IWEVASSOCRESPIE 0x8C08  /* IEs used in (Re)Association
                                 * Response. The data includes id and
                                 * length fields and may contain more
                                 * than one IE. This may be sent
                                 * between IWEVASSOCREQIE and
                                 * IWEVREGISTERED events for the
                                 * association. */
#define IWEVPMKIDCAND   0x8C09  /* PMKID candidate for RSN
                                 * pre-authentication
                                 * (struct iw_pmkid_cand) */

#define IWEVTXDROP	0x8C00		/* Packet dropped to excessive retry */
#define IWEVQUAL	0x8C01		/* Quality part of statistics (scan) */
#define IWEVCUSTOM	0x8C02		/* Driver specific ascii string */
#define IWEVREGISTERED	0x8C03		/* Discovered a new node (AP mode) */
#define IWEVEXPIRED	0x8C04		/* Expired a node (AP mode) */
#define IWEVGENIE	0x8C05		/* Generic IE (WPA, RSN, WMM, ..)
					 * (scan results); This includes id and
					 * length fields. One IWEVGENIE may
					 * contain more than one IE. Scan
					 * results may contain one or more
					 * IWEVGENIE events. */
#define IWEVMICHAELMICFAILURE 0x8C06	/* Michael MIC failure
					 * (struct iw_michaelmicfailure)
					 */
#define IWEVASSOCREQIE	0x8C07		/* IEs used in (Re)Association Request.
					 * The data includes id and length
					 * fields and may contain more than one
					 * IE. This event is required in
					 * Managed mode if the driver
					 * generates its own WPA/RSN IE. This
					 * should be sent just before
					 * IWEVREGISTERED event for the
					 * association. */
#define IWEVASSOCRESPIE	0x8C08		/* IEs used in (Re)Association
					 * Response. The data includes id and
					 * length fields and may contain more
					 * than one IE. This may be sent
					 * between IWEVASSOCREQIE and
					 * IWEVREGISTERED events for the
					 * association. */
#define IWEVPMKIDCAND	0x8C09		/* PMKID candidate for RSN
					 * pre-authentication
					 * (struct iw_pmkid_cand) */


/* Wireless Identification */
#define SIOCSIWCOMMIT	0x8B00		/* Commit pending changes to driver */
#define SIOCGIWNAME	0x8B01		/* get name == wireless protocol */
/* SIOCGIWNAME is used to verify the presence of Wireless Extensions.
 * Common values : "IEEE 802.11-DS", "IEEE 802.11-FH", "IEEE 802.11b"...
 * Don't put the name of your driver there, it's useless. */

/* Basic operations */
#define SIOCSIWNWID	0x8B02		/* set network id (pre-802.11) */
#define SIOCGIWNWID	0x8B03		/* get network id (the cell) */
#define SIOCSIWFREQ	0x8B04		/* set channel/frequency (Hz) */
#define SIOCGIWFREQ	0x8B05		/* get channel/frequency (Hz) */
#define SIOCSIWMODE	0x8B06		/* set operation mode */
#define SIOCGIWMODE	0x8B07		/* get operation mode */
#define SIOCSIWSENS	0x8B08		/* set sensitivity (dBm) */
#define SIOCGIWSENS	0x8B09		/* get sensitivity (dBm) */

/* Informative stuff */
#define SIOCSIWRANGE	0x8B0A		/* Unused */
#define SIOCGIWRANGE	0x8B0B		/* Get range of parameters */
#define SIOCSIWPRIV	0x8B0C		/* Unused */
#define SIOCGIWPRIV	0x8B0D		/* get private ioctl interface info */
#define SIOCSIWSTATS	0x8B0E		/* Unused */
#define SIOCGIWSTATS	0x8B0F		/* Get /proc/net/wireless stats */
/* SIOCGIWSTATS is strictly used between user space and the kernel, and
 * is never passed to the driver (i.e. the driver will never see it). */

/* Spy support (statistics per MAC address - used for Mobile IP support) */
#define SIOCSIWSPY	0x8B10		/* set spy addresses */
#define SIOCGIWSPY	0x8B11		/* get spy info (quality of link) */
#define SIOCSIWTHRSPY	0x8B12		/* set spy threshold (spy event) */
#define SIOCGIWTHRSPY	0x8B13		/* get spy threshold */

/* Access Point manipulation */
#define SIOCSIWAP	0x8B14		/* set access point MAC addresses */
#define SIOCGIWAP	0x8B15		/* get access point MAC addresses */
#define SIOCGIWAPLIST	0x8B17		/* Deprecated in favor of scanning */
#define SIOCSIWSCAN	0x8B18		/* trigger scanning (list cells) */
#define SIOCGIWSCAN	0x8B19		/* get scanning results */

/* 802.11 specific support */
#define SIOCSIWESSID	0x8B1A		/* set ESSID (network name) */
#define SIOCGIWESSID	0x8B1B		/* get ESSID */
#define SIOCSIWNICKN	0x8B1C		/* set node name/nickname */
#define SIOCGIWNICKN	0x8B1D		/* get node name/nickname */
/* As the ESSID and NICKN are strings up to 32 bytes long, it doesn't fit
 * within the 'iwreq' structure, so we need to use the 'data' member to
 * point to a string in user space, like it is done for RANGE... */

/* Other parameters useful in 802.11 and some other devices */
#define SIOCSIWRATE	0x8B20		/* set default bit rate (bps) */
#define SIOCGIWRATE	0x8B21		/* get default bit rate (bps) */
#define SIOCSIWRTS	0x8B22		/* set RTS/CTS threshold (bytes) */
#define SIOCGIWRTS	0x8B23		/* get RTS/CTS threshold (bytes) */
#define SIOCSIWFRAG	0x8B24		/* set fragmentation thr (bytes) */
#define SIOCGIWFRAG	0x8B25		/* get fragmentation thr (bytes) */
#define SIOCSIWTXPOW	0x8B26		/* set transmit power (dBm) */
#define SIOCGIWTXPOW	0x8B27		/* get transmit power (dBm) */
#define SIOCSIWRETRY	0x8B28		/* set retry limits and lifetime */
#define SIOCGIWRETRY	0x8B29		/* get retry limits and lifetime */

/* Encoding stuff (scrambling, hardware security, WEP...) */
#define SIOCSIWENCODE	0x8B2A		/* set encoding token & mode */
#define SIOCGIWENCODE	0x8B2B		/* get encoding token & mode */
/* Power saving stuff (power management, unicast and multicast) */
#define SIOCSIWPOWER	0x8B2C		/* set Power Management settings */
#define SIOCGIWPOWER	0x8B2D		/* get Power Management settings */

/* WPA : Generic IEEE 802.11 informatiom element (e.g., for WPA/RSN/WMM).
 * This ioctl uses struct iw_point and data buffer that includes IE id and len
 * fields. More than one IE may be included in the request. Setting the generic
 * IE to empty buffer (len=0) removes the generic IE from the driver. Drivers
 * are allowed to generate their own WPA/RSN IEs, but in these cases, drivers
 * are required to report the used IE as a wireless event, e.g., when
 * associating with an AP. */
#define SIOCSIWGENIE	0x8B30		/* set generic IE */
#define SIOCGIWGENIE	0x8B31		/* get generic IE */

/* WPA : IEEE 802.11 MLME requests */
#define SIOCSIWMLME	0x8B16		/* request MLME operation; uses
					 * struct iw_mlme */
/* WPA : Authentication mode parameters */
#define SIOCSIWAUTH	0x8B32		/* set authentication mode params */
#define SIOCGIWAUTH	0x8B33		/* get authentication mode params */

/* WPA : Extended version of encoding configuration */
#define SIOCSIWENCODEEXT 0x8B34		/* set encoding token & mode */
#define SIOCGIWENCODEEXT 0x8B35		/* get encoding token & mode */

/* WPA2 : PMKSA cache management */
#define SIOCSIWPMKSA	0x8B36		/* PMKSA cache operation */

/* --------------------------- SUBTYPES --------------------------- */
/*
 *	For all data larger than 16 octets, we need to use a
 *	pointer to memory allocated in user space.
 */
struct	iw_point
{
  void   	*pointer;	/* Pointer to the data  (in user space) */
  uint16_t		length;		/* number of fields or size in bytes */
  uint16_t		flags;		/* Optional params */
};


/* ------------------------ IOCTL REQUEST ------------------------ */
/*
 *	Generic format for most parameters that fit in an int
 */
struct	iw_param
{
  int32_t		value;		/* The value of the parameter itself */
  uint8_t		fixed;		/* Hardware should not use auto select */
  uint8_t		disabled;	/* Disable the feature */
  uint16_t		flags;		/* Various specifc flags (if any) */
};
/*
 *	A frequency
 *	For numbers lower than 10^9, we encode the number in 'm' and
 *	set 'e' to 0
 *	For number greater than 10^9, we divide it by the lowest power
 *	of 10 to get 'm' lower than 10^9, with 'm'= f / (10^'e')...
 *	The power of 10 is in 'e', the result of the division is in 'm'.
 */
struct	iw_freq
{
	int32_t		m;		/* Mantissa */
	int16_t		e;		/* Exponent */
	uint8_t		i;		/* List index (when in range struct) */
	uint8_t		flags;		/* Flags (fixed/auto) */
};

/*
 *	Quality of the link
 */
struct	iw_quality
{
	uint8_t		qual;		/* link quality (%retries, SNR,
					   %missed beacons or better...) */
	uint8_t		level;		/* signal level (dBm) */
	uint8_t		noise;		/* noise level (dBm) */
	uint8_t		updated;	/* Flags to know if updated */
};

/*
 *	Packet discarded in the wireless adapter due to
 *	"wireless" specific problems...
 *	Note : the list of counter and statistics in net_device_stats
 *	is already pretty exhaustive, and you should use that first.
 *	This is only additional stats...
 */
struct	iw_discarded
{
	uint32_t		nwid;		/* Rx : Wrong nwid/essid */
	uint32_t		code;		/* Rx : Unable to code/decode (WEP) */
	uint32_t		fragment;	/* Rx : Can't perform MAC reassembly */
	uint32_t		retries;	/* Tx : Max MAC retries num reached */
	uint32_t		misc;		/* Others cases */
};

/*
 *	Packet/Time period missed in the wireless adapter due to
 *	"wireless" specific problems...
 */
struct	iw_missed
{
	uint32_t		beacon;		/* Missed beacons/superframe */
};

/*
 * This structure defines the payload of an ioctl, and is used
 * below.
 *
 * Note that this structure should fit on the memory footprint
 * of iwreq (which is the same as ifreq), which mean a max size of
 * 16 octets = 128 bits. Warning, pointers might be 64 bits wide...
 * You should check this when increasing the structures defined
 * above in this file...
 */
union	iwreq_data
{
	/* Config - generic */
	char		name[IFNAMSIZ];
	/* Name : used to verify the presence of  wireless extensions.
	 * Name of the protocol/provider... */

	struct iw_point	essid;		/* Extended network name */
	struct iw_param	nwid;		/* network id (or domain - the cell) */
	struct iw_freq	freq;		/* frequency or channel :
					 * 0-1000 = channel
					 * > 1000 = frequency in Hz */

	struct iw_param	sens;		/* signal level threshold */
	struct iw_param	bitrate;	/* default bit rate */
	struct iw_param	txpower;	/* default transmit power */
	struct iw_param	rts;		/* RTS threshold threshold */
	struct iw_param	frag;		/* Fragmentation threshold */
	uint32_t		mode;		/* Operation mode */
	struct iw_param	retry;		/* Retry limits & lifetime */

	struct iw_point	encoding;	/* Encoding stuff : tokens */
	struct iw_param	power;		/* PM duration/timeout */
	struct iw_quality qual;		/* Quality part of statistics */

	struct sockaddr	ap_addr;	/* Access point address */
	struct sockaddr	addr;		/* Destination address (hw/mac) */

	struct iw_param	param;		/* Other small parameters */
	struct iw_point	data;		/* Other large parameters */
};

/*
 * The structure to exchange data for ioctl.
 * This structure is the same as 'struct ifreq', but (re)defined for
 * convenience...
 * Do I need to remind you about structure size (32 octets) ?
 */
struct	iwreq
{
	char	ifr_name[IFNAMSIZ];	/* if name, e.g. "eth0" */

	/* Data part (defined just above) */
	union	iwreq_data	u;
};

/* -------------------------- IOCTL DATA -------------------------- */
/*
 *	For those ioctl which want to exchange mode data that what could
 *	fit in the above structure...
 */

/*
 *	Range of parameters
 */
#define SCAN_SSID_MAX    2

/* Maximum frequencies in the range struct */
#define IW_MAX_FREQUENCIES	32
/* Note : if you have something like 80 frequencies,
 * don't increase this constant and don't fill the frequency list.
 * The user will be able to set by channel anyway... */

/* Maximum bit rates in the range struct */
#define IW_MAX_BITRATES		32

/* Maximum tx powers in the range struct */
#define IW_MAX_TXPOWER		8
/* Note : if you more than 8 TXPowers, just set the max and min or
 * a few of them in the struct iw_range. */

/* Maximum of address that you may set with SPY */
#define IW_MAX_SPY		8

/* Maximum of address that you may get in the
   list of access points in range */
#define IW_MAX_AP		64

/* Maximum size of the ESSID and NICKN strings */
#define IW_ESSID_MAX_SIZE	32
/* Maximum number of size of encoding token available
 * they are listed in the range structure */
#define IW_MAX_ENCODING_SIZES	8

/* Maximum size of the encoding token in bytes */
#define IW_ENCODING_TOKEN_MAX	64	/* 512 bits (for now) */

struct	iw_range
{
	/* Informative stuff (to choose between different interface) */
	uint32_t		throughput;	/* To give an idea... */
	/* In theory this value should be the maximum benchmarked
	 * TCP/IP throughput, because with most of these devices the
	 * bit rate is meaningless (overhead an co) to estimate how
	 * fast the connection will go and pick the fastest one.
	 * I suggest people to play with Netperf or any benchmark...
	 */

	/* NWID (or domain id) */
	uint32_t		min_nwid;	/* Minimal NWID we are able to set */
	uint32_t		max_nwid;	/* Maximal NWID we are able to set */

	/* Old Frequency (backward compat - moved lower ) */
	uint16_t		old_num_channels;
	uint8_t		old_num_frequency;

	/* Scan capabilities */
	uint8_t		scan_capa; 	/* IW_SCAN_CAPA_* bit field */

	/* Wireless event capability bitmasks */
	uint32_t		event_capa[6];

	/* signal level threshold range */
	int32_t		sensitivity;

	/* Quality of link & SNR stuff */
	/* Quality range (link, level, noise)
	 * If the quality is absolute, it will be in the range [0 ; max_qual],
	 * if the quality is dBm, it will be in the range [max_qual ; 0].
	 * Don't forget that we use 8 bit arithmetics... */
	struct iw_quality	max_qual;	/* Quality of the link */
	/* This should contain the average/typical values of the quality
	 * indicator. This should be the threshold between a "good" and
	 * a "bad" link (example : monitor going from green to orange).
	 * Currently, user space apps like quality monitors don't have any
	 * way to calibrate the measurement. With this, they can split
	 * the range between 0 and max_qual in different quality level
	 * (using a geometric subdivision centered on the average).
	 * I expect that people doing the user space apps will feedback
	 * us on which value we need to put in each driver... */
	struct iw_quality	avg_qual;	/* Quality of the link */

	/* Rates */
	uint8_t		num_bitrates;	/* Number of entries in the list */
	int32_t		bitrate[IW_MAX_BITRATES];	/* list, in bps */

	/* RTS threshold */
	int32_t		min_rts;	/* Minimal RTS threshold */
	int32_t		max_rts;	/* Maximal RTS threshold */

	/* Frag threshold */
	int32_t		min_frag;	/* Minimal frag threshold */
	int32_t		max_frag;	/* Maximal frag threshold */

	/* Power Management duration & timeout */
	int32_t		min_pmp;	/* Minimal PM period */
	int32_t		max_pmp;	/* Maximal PM period */
	int32_t		min_pmt;	/* Minimal PM timeout */
	int32_t		max_pmt;	/* Maximal PM timeout */
	uint16_t		pmp_flags;	/* How to decode max/min PM period */
	uint16_t		pmt_flags;	/* How to decode max/min PM timeout */
	uint16_t		pm_capa;	/* What PM options are supported */

	/* Encoder stuff */
	uint16_t	encoding_size[IW_MAX_ENCODING_SIZES];	/* Different token sizes */
	uint8_t	num_encoding_sizes;	/* Number of entry in the list */
	uint8_t	max_encoding_tokens;	/* Max number of tokens */
	/* For drivers that need a "login/passwd" form */
	uint8_t	encoding_login_index;	/* token index for login token */

	/* Transmit power */
	uint16_t		txpower_capa;	/* What options are supported */
	uint8_t		num_txpower;	/* Number of entries in the list */
	int32_t		txpower[IW_MAX_TXPOWER];	/* list, in bps */

	/* Wireless Extension version info */
	uint8_t		we_version_compiled;	/* Must be WIRELESS_EXT */
	uint8_t		we_version_source;	/* Last update of source */

	/* Retry limits and lifetime */
	uint16_t		retry_capa;	/* What retry options are supported */
	uint16_t		retry_flags;	/* How to decode max/min retry limit */
	uint16_t		r_time_flags;	/* How to decode max/min retry life */
	int32_t		min_retry;	/* Minimal number of retries */
	int32_t		max_retry;	/* Maximal number of retries */
	int32_t		min_r_time;	/* Minimal retry lifetime */
	int32_t		max_r_time;	/* Maximal retry lifetime */

	/* Frequency */
	uint16_t		num_channels;	/* Number of channels [0; num - 1] */
	uint8_t		num_frequency;	/* Number of entry in the list */
	struct iw_freq	freq[IW_MAX_FREQUENCIES];	/* list */
	/* Note : this frequency list doesn't need to fit channel numbers,
	 * because each entry contain its channel index */

	uint32_t		enc_capa;	/* IW_ENC_CAPA_* bit field */
};

/* ----------------------- WIRELESS EVENTS ----------------------- */
/*
 * Wireless events are carried through the rtnetlink socket to user
 * space. They are encapsulated in the IFLA_WIRELESS field of
 * a RTM_NEWLINK message.
 */

/*
 * A Wireless Event. Contains basically the same data as the ioctl...
 */
struct iw_event
{
	uint16_t		len;			/* Real length of this stuff */
	uint16_t		cmd;			/* Wireless IOCTL */
	union iwreq_data	u;		/* IOCTL fixed payload */
};

/* Size of the Event prefix (including padding and alignement junk) */
#define IW_EV_LCP_LEN	(sizeof(struct iw_event) - sizeof(union iwreq_data))
/* Size of the various events */
#define IW_EV_CHAR_LEN	(IW_EV_LCP_LEN + IFNAMSIZ)
#define IW_EV_UINT_LEN	(IW_EV_LCP_LEN + sizeof(uint32_t))
#define IW_EV_FREQ_LEN	(IW_EV_LCP_LEN + sizeof(struct iw_freq))
#define IW_EV_PARAM_LEN	(IW_EV_LCP_LEN + sizeof(struct iw_param))
#define IW_EV_ADDR_LEN	(IW_EV_LCP_LEN + sizeof(struct sockaddr))
#define IW_EV_QUAL_LEN	(IW_EV_LCP_LEN + sizeof(struct iw_quality))

/* iw_point events are special. First, the payload (extra data) come at
 * the end of the event, so they are bigger than IW_EV_POINT_LEN. Second,
 * we omit the pointer, so start at an offset. */
#define IW_EV_POINT_OFF (((char *) &(((struct iw_point *) NULL)->length)) - \
			  (char *) NULL)
#define IW_EV_POINT_LEN	(IW_EV_LCP_LEN + sizeof(struct iw_point) - \
			 IW_EV_POINT_OFF)

/* MTU to be set for the wlan#ap device; this is mainly needed for IEEE 802.1X
 * frames that might be longer than normal default MTU and they are not
 * fragmented */
#define HOSTAPD_MTU                   2290

/* netdevice private ioctls (used, e.g., with iwpriv from user space) */

/* New wireless extensions API - SET/GET convention (even ioctl numbers are
 * root only)
 */
#define PRISM2_IOCTL_PRISM2_PARAM (SIOCIWFIRSTPRIV + 0)
#define PRISM2_IOCTL_GET_PRISM2_PARAM (SIOCIWFIRSTPRIV + 1)
#define PRISM2_IOCTL_WRITEMIF (SIOCIWFIRSTPRIV + 2)
#define PRISM2_IOCTL_READMIF (SIOCIWFIRSTPRIV + 3)
#define PRISM2_IOCTL_MONITOR (SIOCIWFIRSTPRIV + 4)
#define PRISM2_IOCTL_RESET (SIOCIWFIRSTPRIV + 6)
#define PRISM2_IOCTL_INQUIRE (SIOCIWFIRSTPRIV + 8)
#define PRISM2_IOCTL_WDS_ADD (SIOCIWFIRSTPRIV + 10)
#define PRISM2_IOCTL_WDS_DEL (SIOCIWFIRSTPRIV + 12)
#define PRISM2_IOCTL_SET_RID_WORD (SIOCIWFIRSTPRIV + 14)
#define PRISM2_IOCTL_MACCMD (SIOCIWFIRSTPRIV + 16)
#define PRISM2_IOCTL_ADDMAC (SIOCIWFIRSTPRIV + 18)
#define PRISM2_IOCTL_DELMAC (SIOCIWFIRSTPRIV + 20)
#define PRISM2_IOCTL_KICKMAC (SIOCIWFIRSTPRIV + 22)

/* following are not in SIOCGIWPRIV list; check permission in the driver code
 */
#define PRISM2_IOCTL_DOWNLOAD (SIOCDEVPRIVATE + 13)
#define PRISM2_IOCTL_HOSTAPD (SIOCDEVPRIVATE + 14)


/* PRISM2_IOCTL_PRISM2_PARAM ioctl() subtypes: */
enum {
	/* PRISM2_PARAM_PTYPE = 1, */ /* REMOVED 2003-10-22 */
	PRISM2_PARAM_TXRATECTRL = 2,
	PRISM2_PARAM_BEACON_INT = 3,
	PRISM2_PARAM_PSEUDO_IBSS = 4,
	PRISM2_PARAM_ALC = 5,
	/* PRISM2_PARAM_TXPOWER = 6, */ /* REMOVED 2003-10-22 */
	PRISM2_PARAM_DUMP = 7,
	PRISM2_PARAM_OTHER_AP_POLICY = 8,
	PRISM2_PARAM_AP_MAX_INACTIVITY = 9,
	PRISM2_PARAM_AP_BRIDGE_PACKETS = 10,
	PRISM2_PARAM_DTIM_PERIOD = 11,
	PRISM2_PARAM_AP_NULLFUNC_ACK = 12,
	PRISM2_PARAM_MAX_WDS = 13,
	PRISM2_PARAM_AP_AUTOM_AP_WDS = 14,
	PRISM2_PARAM_AP_AUTH_ALGS = 15,
	PRISM2_PARAM_MONITOR_ALLOW_FCSERR = 16,
	PRISM2_PARAM_HOST_ENCRYPT = 17,
	PRISM2_PARAM_HOST_DECRYPT = 18,
	PRISM2_PARAM_BUS_MASTER_THRESHOLD_RX = 19,
	PRISM2_PARAM_BUS_MASTER_THRESHOLD_TX = 20,
	PRISM2_PARAM_HOST_ROAMING = 21,
	PRISM2_PARAM_BCRX_STA_KEY = 22,
	PRISM2_PARAM_IEEE_802_1X = 23,
	PRISM2_PARAM_ANTSEL_TX = 24,
	PRISM2_PARAM_ANTSEL_RX = 25,
	PRISM2_PARAM_MONITOR_TYPE = 26,
	PRISM2_PARAM_WDS_TYPE = 27,
	PRISM2_PARAM_HOSTSCAN = 28,
	PRISM2_PARAM_AP_SCAN = 29,
	PRISM2_PARAM_ENH_SEC = 30,
	PRISM2_PARAM_IO_DEBUG = 31,
	PRISM2_PARAM_BASIC_RATES = 32,
	PRISM2_PARAM_OPER_RATES = 33,
	PRISM2_PARAM_HOSTAPD = 34,
	PRISM2_PARAM_HOSTAPD_STA = 35,
	PRISM2_PARAM_WPA = 36,
	PRISM2_PARAM_PRIVACY_INVOKED = 37,
	PRISM2_PARAM_TKIP_COUNTERMEASURES = 38,
	PRISM2_PARAM_DROP_UNENCRYPTED = 39,
	PRISM2_PARAM_SCAN_CHANNEL_MASK = 40,
};

enum { HOSTAP_ANTSEL_DO_NOT_TOUCH = 0, HOSTAP_ANTSEL_DIVERSITY = 1,
       HOSTAP_ANTSEL_LOW = 2, HOSTAP_ANTSEL_HIGH = 3 };


/* PRISM2_IOCTL_MACCMD ioctl() subcommands: */
enum { AP_MAC_CMD_POLICY_OPEN = 0, AP_MAC_CMD_POLICY_ALLOW = 1,
       AP_MAC_CMD_POLICY_DENY = 2, AP_MAC_CMD_FLUSH = 3,
       AP_MAC_CMD_KICKALL = 4 };


/* PRISM2_IOCTL_DOWNLOAD ioctl() dl_cmd: */
enum {
	PRISM2_DOWNLOAD_VOLATILE = 1 /* RAM */,
	/* Note! Old versions of prism2_srec have a fatal error in CRC-16
	 * calculation, which will corrupt all non-volatile downloads.
	 * PRISM2_DOWNLOAD_NON_VOLATILE used to be 2, but it is now 3 to
	 * prevent use of old versions of prism2_srec for non-volatile
	 * download. */
	PRISM2_DOWNLOAD_NON_VOLATILE = 3 /* FLASH */,
	PRISM2_DOWNLOAD_VOLATILE_GENESIS = 4 /* RAM in Genesis mode */,
	/* Persistent versions of volatile download commands (keep firmware
	 * data in memory and automatically re-download after hw_reset */
	PRISM2_DOWNLOAD_VOLATILE_PERSISTENT = 5,
	PRISM2_DOWNLOAD_VOLATILE_GENESIS_PERSISTENT = 6,
};

struct prism2_download_param {
	uint32_t dl_cmd;
	uint32_t start_addr;
	uint32_t num_areas;

	struct prism2_download_area {
		uint32_t addr; /* wlan card address */
		uint32_t len;
		c_addr_t ptr; /* pointer to data in user space */
	} *data;
};

#define PRISM2_MAX_DOWNLOAD_AREA_LEN 131072
#define PRISM2_MAX_DOWNLOAD_LEN 262144


/* PRISM2_IOCTL_HOSTAPD ioctl() cmd: */
enum {
	PRISM2_HOSTAPD_FLUSH = 1,
	PRISM2_HOSTAPD_ADD_STA = 2,
	PRISM2_HOSTAPD_REMOVE_STA = 3,
	PRISM2_HOSTAPD_GET_INFO_STA = 4,

	/* REMOVED: PRISM2_HOSTAPD_RESET_TXEXC_STA = 5, */
	PRISM2_SET_ENCRYPTION = 6,
	PRISM2_GET_ENCRYPTION = 7,
	PRISM2_HOSTAPD_SET_FLAGS_STA = 8,
	PRISM2_HOSTAPD_GET_RID = 9,
	PRISM2_HOSTAPD_SET_RID = 10,
	PRISM2_HOSTAPD_SET_ASSOC_AP_ADDR = 11,
	PRISM2_HOSTAPD_SET_GENERIC_ELEMENT = 12,
	PRISM2_HOSTAPD_MLME = 13,
	PRISM2_HOSTAPD_SCAN_REQ = 14,
	PRISM2_HOSTAPD_STA_CLEAR_STATS = 15,
	PRISM2_HOSTAPD_GET_SCAN_RESULT = 16,
	PRISM2_HOSTAPD_ASSOC_REQ = 17,
	PRISM2_HOSTAPD_ASSOC_ACK = 18,

	PRISM2_HOSTAPD_REG_SCAN_CALLBACK = 19,
	PRISM2_HOSTAPD_REG_ASSOC_CALLBACK = 20,
	PRISM2_HOSTAPD_REG_DISASSOC_CALLBACK = 21,
	PRISM2_HOSTAPD_REG_DEAUTH_CALLBACK = 22,
	PRISM2_HOSTAPD_REG_APP_START = 23,

	PRISM2_HOSTAPD_DISCONN_REQ = 24,
	PRISM2_HOSTAPD_WPA_INIT_VIF = 25,
	PRISM2_HOSTAPD_WPA_DEINIT_VIF = 26,
	PRISM2_HOSTAPD_START_APM = 27,
	PRISM2_HOSTAPD_SET_AP_BCN = 28,
    PRISM2_HOSTAPD_GET_BSS_INFO = 29,
    PRISM2_HOSTAPD_CHANNEL_SWITCH = 30,
	PRISM2_HOSTAPD_STOP_APM = 31,

	PRISM2_HOSTAPD_REG_CSA_CALLBACK = 32,
	PRISM2_HOSTAPD_POLL_CLIENT_NULL_DATA = 33,

#if CFG_MESH
	PRISM2_HOSTAPD_JOIN_MESH = 34,
	PRISM2_HOSTAPD_LEAVE_MESH = 35,
#endif

#ifdef CONFIG_SME
	PRISM2_HOSTAPD_AUTHENTICATE = 36,
	PRISM2_HOSTAPD_REG_AUTH_CALLBACK,
	PRISM2_HOSTAPD_SET_OPER_STATE,
#endif
	PRISM2_HOSTAPD_EXTERNAL_AUTH_STATUS,

};

#define PRISM2_HOSTAPD_MAX_BUF_SIZE 1024
#define PRISM2_HOSTAPD_RID_HDR_LEN \
((size_t) (&((struct prism2_hostapd_param *) 0)->u.rid.data))
#define PRISM2_HOSTAPD_GENERIC_ELEMENT_HDR_LEN \
((size_t) (&((struct prism2_hostapd_param *) 0)->u.generic_elem.data))

/* Maximum length for algorithm names (-1 for nul termination) used in ioctl()
 */
#define HOSTAP_CRYPT_ALG_NAME_LEN 16
#define HOSTAP_AUTH_OPEN    0
#define HOSTAP_AUTH_SHARED  1
#define HOSTAP_AUTH_SAE		3

struct prism2_hostapd_param {
	uint32_t cmd;
	uint8_t sta_addr[ETH_ALEN];
    uint8_t vif_idx ;

	union {
		struct{
			uint8_t* own_addr;
			uint8_t* sta_addr;
		}poll_null_data;

		struct {
			FUNC_2PARAM_PTR cb;
			void *arg;
		} reg_scan_cfm;

		struct {
			FUNC_2PARAM_PTR cb;
			void *arg;
		} reg_assoc_cfm;

		struct {
			FUNC_2PARAM_PTR cb;
			void *arg;
		} reg_auth_cfm;

		struct {
			FUNC_2PARAM_PTR cb;
			void *arg;
		} reg_disassoc_evt, reg_deauth_evt;

		struct {
			uint16_t aid;
			uint16_t capability;
			uint8_t tx_supp_rates;
			uint8_t plink_state;
			uint8_t set;
			void *arg;
		} add_sta;

        struct {
            uint32_t type;
			uint8_t* indx_ptr;
		} add_if;

		struct {
			uint32_t inactive_sec;
		} get_info_sta;

        struct {
            void *beacon;
            uint16_t bcn_len;
            uint16_t head_len;
            uint8_t tim_len;
        } bcn_change;

		struct {
			uint8_t alg[HOSTAP_CRYPT_ALG_NAME_LEN];
			uint32_t flags;
			uint32_t err;
			uint8_t idx;
			uint8_t seq[8]; /* sequence counter (set: RX, get: TX) */
			uint16_t key_len;
			uint8_t key[0];
		} crypt;

		struct {
			uint32_t flags_and;
			uint32_t flags_or;
		} set_flags_sta;

		struct {
			uint16_t rid;
			uint16_t len;
			uint8_t data[0];
		} rid;

		struct {
			uint8_t len;
			uint8_t data[0];
		} generic_elem;

		struct {
#define MLME_STA_DEAUTH 0
#define MLME_STA_DISASSOC 1
			uint16_t cmd;
			uint16_t reason_code;
		} mlme;

		struct {
			struct {
				uint8_t ssid_len;
				uint8_t ssid[SSID_MAX_LEN];
#if CFG_SUPPORT_BSSID_CONNECT
				uint8_t bssid[ETH_ALEN];
#endif
			}ssids[SCAN_SSID_MAX];
			uint8_t ssids_num;
			int freqs[14];		//FIXME: 5G
		} scan_req;

		struct wpa_scan_results *scan_rst;

		struct {
			uint8_t bssid[ETH_ALEN];
			uint8_t ssid[SSID_MAX_LEN];
			uint8_t ssid_len;
			uint16_t freq;
			uint8_t proto;			// wpa proto: wpa or rsn
			uint32_t key_mgmt_suite;	//
			uint32_t pairwise_suite;
			uint32_t group_suite;
			uint8_t auth_alg;
			uint8_t mfp;
			uint16_t ie_len;
			uint32_t ie_buf[64];		// assoc ie
			uint16_t bcn_len;
			uint8_t bcn_buf[0];
		} assoc_req;

#ifdef CONFIG_SME
		struct {
			uint8_t bssid[ETH_ALEN];
			uint8_t ssid[SSID_MAX_LEN];
			uint8_t ssid_len;
			uint16_t freq;
			uint8_t auth_alg;
			uint16_t ie_len;
			uint8_t ie[128];
			uint16_t sae_data_len;
			uint8_t sae_data[0];
		} authen_req;
#endif

		struct {
			uint32_t reason;
		} disconnect_req;

		struct {
			uint32_t freq;
			uint32_t csa_cnt;

            struct csa_settings *settings;
		} chan_switch;

		struct {
			FUNC_2PARAM_PTR cb;
			void *arg;
		} reg_csa_event;

		struct {
			uint8_t bssid[ETH_ALEN];
			uint8_t ssid[SSID_MAX_LEN];
		} bss_info;
#if CFG_MESH
		struct {
			FUNC_2PARAM_PTR cb;
			void *arg;
		} mesh_join_req;
#endif

		struct {
			int state;
		} oper_state;

		struct {
			uint16_t status;
		} external_auth_status;

	} u;
};

#define HOSTAP_CRYPT_FLAG_SET_TX_KEY          BIT(0)
#define HOSTAP_CRYPT_FLAG_PERMANENT           BIT(1)

#define HOSTAP_CRYPT_ERR_UNKNOWN_ALG          2
#define HOSTAP_CRYPT_ERR_UNKNOWN_ADDR         3
#define HOSTAP_CRYPT_ERR_CRYPT_INIT_FAILED    4
#define HOSTAP_CRYPT_ERR_KEY_SET_FAILED       5
#define HOSTAP_CRYPT_ERR_TX_KEY_SET_FAILED    6
#define HOSTAP_CRYPT_ERR_CARD_CONF_FAILED     7

void wpa_handler_signal(void *arg, uint8_t vif_idx);
void wpa_driver_scan_sig_handler(int sig, void *signal_ctx);
void wpa_driver_assoc_sig_handler(int sig, void *signal_ctx);
void wpa_driver_disassoc_sig_handler(int sig, void *signal_ctx);
void wpa_driver_deauth_sig_handler(int sig, void *signal_ctx);
void wpa_driver_csa_sig_handler(int sig, void *signal_ctx);

#endif /* HOSTAP_DRIVER_H */
