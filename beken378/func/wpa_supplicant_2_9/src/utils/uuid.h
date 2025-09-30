#include <stdint.h>
/*
 * Universally Unique IDentifier (UUID)
 * Copyright (c) 2008, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef UUID_H
#define UUID_H

#define UUID_LEN 16

int uuid_str2bin(const char *str, uint8_t *bin);
int uuid_bin2str(const uint8_t *bin, char *str, size_t max_len);
int is_nil_uuid(const uint8_t *uuid);
int uuid_random(uint8_t *uuid);

#endif /* UUID_H */
