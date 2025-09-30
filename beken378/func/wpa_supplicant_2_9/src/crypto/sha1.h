#include <stdint.h>
/*
 * SHA1 hash implementation and interface functions
 * Copyright (c) 2003-2009, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef SHA1_H
#define SHA1_H

#define SHA1_MAC_LEN 20

int hmac_sha1_vector(const uint8_t *key, size_t key_len, size_t num_elem,
		     const uint8_t *addr[], const size_t *len, uint8_t *mac);
int hmac_sha1(const uint8_t *key, size_t key_len, const uint8_t *data, size_t data_len,
	       uint8_t *mac);
int sha1_prf(const uint8_t *key, size_t key_len, const char *label,
	     const uint8_t *data, size_t data_len, uint8_t *buf, size_t buf_len);
int sha1_t_prf(const uint8_t *key, size_t key_len, const char *label,
	       const uint8_t *seed, size_t seed_len, uint8_t *buf, size_t buf_len);
int __must_check tls_prf_sha1_md5(const uint8_t *secret, size_t secret_len,
				  const char *label, const uint8_t *seed,
				  size_t seed_len, uint8_t *out, size_t outlen);
int pbkdf2_sha1(const char *passphrase, const uint8_t *ssid, size_t ssid_len,
		int iterations, uint8_t *buf, size_t buflen);
#endif /* SHA1_H */
