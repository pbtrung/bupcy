#include <assert.h>

#include "crypto/key.h"
#include "utils/common.h"

void key_master_derive(const unsigned char *pwd, uint32_t pwd_len,
                       const unsigned char *salt, key_master_t *key_master) {
    assert(pwd != NULL);
    assert(pwd_len >= KEY_MASTER_PWD_MIN_LEN);
    assert(salt != NULL);
    assert(key_master != NULL);

    rc_t rc = BUPCY_SUCCESS;
    uint32_t t = 9;
    uint32_t m = 1 << 19;
    uint32_t p = 2;

    unsigned char *master_key =
        bupcy_malloc(KEY_MASTER_TOTAL_LEN * sizeof(unsigned char));

    rc = argon2i_hash_raw(t, m, p, pwd, pwd_len, salt, KEY_MASTER_SALT_LEN,
                          master_key, KEY_MASTER_TOTAL_LEN);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_ARGON2_ERR);

    memcpy(key_master->master_enc_key, master_key, KEY_MASTER_ENC_KEY_LEN);
    memcpy(key_master->hash_key, &master_key[KEY_MASTER_ENC_KEY_LEN],
           KEY_MASTER_HASH_KEY_LEN);
    memcpy(key_master->id_key,
           &master_key[KEY_MASTER_ENC_KEY_LEN + KEY_MASTER_HASH_KEY_LEN],
           KEY_MASTER_ID_KEY_LEN);

    bupcy_free(master_key);
}

void key_chunk_derive(key_chunk_t *key_chunk, key_master_t *key_master,
                      const unsigned char *chunk_salt) {
    assert(key_chunk != NULL);
    assert(key_master != NULL);
    assert(chunk_salt != NULL);

    rc_t rc = BUPCY_SUCCESS;
    uint32_t t = 3;
    uint32_t m = 1 << 14;
    uint32_t p = 2;

    unsigned char *total_key_chunk =
        bupcy_malloc(KEY_CHUNK_TOTAL_LEN * sizeof(unsigned char));

    rc = argon2i_hash_raw(
             t, m, p, key_master->master_enc_key, KEY_MASTER_ENC_KEY_LEN, chunk_salt,
             KEY_CHUNK_SALT_LEN, total_key_chunk, KEY_CHUNK_TOTAL_LEN);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_ARGON2_ERR);

    memcpy(key_chunk->enc_key, total_key_chunk, KEY_CHUNK_ENC_KEY_LEN);
    memcpy(key_chunk->hc256_kiv, &total_key_chunk[KEY_CHUNK_ENC_KEY_LEN],
           KEY_CHUNK_HC256_KIV_LEN);
    memcpy(key_chunk->ctr_iv,
           &total_key_chunk[KEY_CHUNK_ENC_KEY_LEN + KEY_CHUNK_HC256_KIV_LEN],
           KEY_CHUNK_CTR_IV_LEN);
    memcpy(key_chunk->tweak,
           &total_key_chunk[KEY_CHUNK_ENC_KEY_LEN + KEY_CHUNK_HC256_KIV_LEN +
                                                  KEY_CHUNK_CTR_IV_LEN],
           KEY_CHUNK_TWEAK_LEN);
    memcpy(key_chunk->mac_key,
           &total_key_chunk[KEY_CHUNK_ENC_KEY_LEN + KEY_CHUNK_HC256_KIV_LEN +
                                                  KEY_CHUNK_CTR_IV_LEN + KEY_CHUNK_TWEAK_LEN],
           KEY_CHUNK_MAC_KEY_LEN);

    bupcy_free(total_key_chunk);
}
