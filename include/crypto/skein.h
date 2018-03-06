#ifndef SKEIN_H
#define SKEIN_H

#include "skein3fish/skeinApi.h"
#include "utils/rc.h"

#define SKEIN_HASH_LEN 64U
#define SKEIN_MAC_KEY_LEN 64U
#define SKEIN_MAC_LEN 64U

void skein_hash(const unsigned char *input, size_t in_len,
                unsigned char *output);
void skein_mac(const unsigned char *skein_mac_key, const unsigned char *input,
               size_t in_len, unsigned char *output);
void skein_mac_init(SkeinCtx_t *skein_x, const unsigned char *skein_mac_key);
void skein_mac_update(SkeinCtx_t *skein_x, const unsigned char *input,
                      size_t in_len);
void skein_mac_final(SkeinCtx_t *skein_x, unsigned char *output);

#endif // SKEIN_H
