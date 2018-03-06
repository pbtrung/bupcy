#ifndef KEY_H
#define KEY_H

#include "argon2/argon2.h"
#include "crypto/skein.h"
#include "crypto/threefish.h"
#include "hc256/hc256.h"

#define KEY_MASTER_PWD_MIN_LEN 32U
#define KEY_MASTER_SALT_LEN 32U

#define KEY_MASTER_HASH_KEY_LEN SKEIN_MAC_KEY_LEN
#define KEY_MASTER_ID_KEY_LEN SKEIN_MAC_KEY_LEN
#define KEY_MASTER_ENC_KEY_LEN THREEFISH_KEY_LEN

#define KEY_CHUNK_ENC_KEY_LEN THREEFISH_KEY_LEN
#define KEY_CHUNK_HC256_KIV_LEN HC256_KIV_LEN
#define KEY_CHUNK_CTR_IV_LEN THREEFISH_BLOCK_LEN
#define KEY_CHUNK_TWEAK_LEN THREEFISH_TWEAK_LEN
#define KEY_CHUNK_MAC_KEY_LEN SKEIN_MAC_KEY_LEN
#define KEY_CHUNK_SALT_LEN 32U

#define KEY_MASTER_TOTAL_LEN                                                   \
    (KEY_MASTER_ENC_KEY_LEN + KEY_MASTER_HASH_KEY_LEN + KEY_MASTER_ID_KEY_LEN)

#define KEY_CHUNK_TOTAL_LEN                                                    \
    (KEY_CHUNK_ENC_KEY_LEN + KEY_CHUNK_HC256_KIV_LEN + KEY_CHUNK_CTR_IV_LEN +  \
     KEY_CHUNK_TWEAK_LEN + KEY_CHUNK_MAC_KEY_LEN)

struct key_master_t {
    unsigned char master_enc_key[KEY_MASTER_ENC_KEY_LEN];
    unsigned char hash_key[KEY_MASTER_HASH_KEY_LEN];
    unsigned char id_key[KEY_MASTER_ID_KEY_LEN];
};
typedef struct key_master_t key_master_t;

struct key_chunk_t {
    unsigned char enc_key[KEY_CHUNK_ENC_KEY_LEN];
    unsigned char hc256_kiv[KEY_CHUNK_HC256_KIV_LEN];
    unsigned char ctr_iv[KEY_CHUNK_CTR_IV_LEN];
    unsigned char tweak[KEY_CHUNK_TWEAK_LEN];
    unsigned char mac_key[KEY_CHUNK_MAC_KEY_LEN];
};
typedef struct key_chunk_t key_chunk_t;

void key_master_derive(const unsigned char *pwd, uint32_t pwd_len,
                       const unsigned char *salt, key_master_t *key_master);
void key_chunk_derive(key_chunk_t *key_chunk, key_master_t *key_master,
                      const unsigned char *chunk_salt);

#endif // KEY_H
