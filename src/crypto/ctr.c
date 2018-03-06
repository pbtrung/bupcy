#include <assert.h>
#include <stdlib.h>

#include "crypto/ctr.h"
#include "utils/common.h"

void ctr_init(ctr_ctx_t *ctr_x, key_chunk_t *key_chunk) {
    assert(ctr_x != NULL);
    assert(key_chunk != NULL);

    t3f_set_key(ctr_x->t3f_x, (uint64_t *)key_chunk->enc_key,
                (uint64_t *)key_chunk->tweak);
    hc256_set_kiv(ctr_x->hc256_x, key_chunk->hc256_kiv);
    ctr_x->is_hc256_used = false;
}

void ctr_set_hc256_kiv(ctr_ctx_t *ctr_x, key_chunk_t *key_chunk) {
    assert(ctr_x != NULL);
    assert(key_chunk != NULL);

    hc256_set_kiv(ctr_x->hc256_x, key_chunk->hc256_kiv);
    ctr_x->is_hc256_used = false;
}

void ctr_encrypt(ctr_ctx_t *ctr_x, unsigned char *input, size_t in_len,
                 unsigned char *output, unsigned char *ctr_iv) {
    assert(ctr_x != NULL);
    assert(input != NULL);
    assert(in_len > 0);
    assert(output != NULL);
    assert(ctr_iv != NULL);

    check_log_exception(ctr_x->is_hc256_used == true, BUPCY_CTR_HC256_USED_ERR);

    // hc256_gen_bytes uses XOR so counter must be zerod
    unsigned char *counter = bupcy_calloc(CTR_COUNTER_LEN, sizeof(unsigned char));
    unsigned char *t3f_buf =
        bupcy_malloc(THREEFISH_BLOCK_LEN * sizeof(unsigned char));
    unsigned char *ctr_iv_counter =
        bupcy_malloc(THREEFISH_BLOCK_LEN * sizeof(unsigned char));

    memcpy(ctr_iv_counter, ctr_iv, THREEFISH_BLOCK_LEN);

    uint32_t i = 0;
    for (; in_len >= THREEFISH_BLOCK_LEN; ++i, in_len -= THREEFISH_BLOCK_LEN) {
        hc256_gen_bytes(ctr_x->hc256_x, counter, CTR_COUNTER_LEN);
        for (uint32_t j = 0; j < CTR_COUNTER_LEN; ++j) {
            ctr_iv_counter[j] = ctr_iv[j] ^ counter[j];
        }

        t3f_encrypt(ctr_x->t3f_x, ctr_iv_counter, t3f_buf);
        for (uint32_t j = 0; j < THREEFISH_BLOCK_LEN; ++j) {
            output[i * THREEFISH_BLOCK_LEN + j] =
                input[i * THREEFISH_BLOCK_LEN + j] ^ t3f_buf[j];
        }
    }
    if (in_len > 0) {
        hc256_gen_bytes(ctr_x->hc256_x, counter, CTR_COUNTER_LEN);
        for (uint32_t j = 0; j < CTR_COUNTER_LEN; ++j) {
            ctr_iv_counter[j] = ctr_iv[j] ^ counter[j];
        }

        t3f_encrypt(ctr_x->t3f_x, ctr_iv_counter, t3f_buf);
        for (uint32_t j = 0; j < in_len; ++j) {
            output[i * THREEFISH_BLOCK_LEN + j] =
                input[i * THREEFISH_BLOCK_LEN + j] ^ t3f_buf[j];
        }
    }
    ctr_x->is_hc256_used = true;

    bupcy_free(ctr_iv_counter);
    bupcy_free(t3f_buf);
    bupcy_free(counter);
}

void ctr_decrypt(ctr_ctx_t *ctr_x, unsigned char *input, size_t in_len,
                 unsigned char *output, unsigned char *ctr_iv) {
    assert(ctr_x != NULL);
    check_log_exception(ctr_x->is_hc256_used == true, BUPCY_CTR_HC256_USED_ERR);
    ctr_encrypt(ctr_x, input, in_len, output, ctr_iv);
}
