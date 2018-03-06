#ifndef CTR_H
#define CTR_H

#include "crypto/key.h"
#include "utils/common.h"

#define CTR_COUNTER_LEN 32U

struct ctr_ctx_t {
    ThreefishKey_t *t3f_x;
    hc256_ctx_t *hc256_x;
    bool is_hc256_used;
};
typedef struct ctr_ctx_t ctr_ctx_t;

void ctr_init(ctr_ctx_t *ctr_x, key_chunk_t *key_chunk);
void ctr_set_hc256_kiv(ctr_ctx_t *ctr_x, key_chunk_t *key_chunk);
void ctr_encrypt(ctr_ctx_t *ctr_x, unsigned char *input, size_t in_len,
                 unsigned char *output, unsigned char *ctr_iv);
void ctr_decrypt(ctr_ctx_t *ctr_x, unsigned char *input, size_t in_len,
                 unsigned char *output, unsigned char *ctr_iv);

#endif // CTR_H
