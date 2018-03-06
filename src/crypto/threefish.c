#include <assert.h>

#include "crypto/threefish.h"

void t3f_set_key(ThreefishKey_t *t3f_x, uint64_t *t3f_key,
                 uint64_t *t3f_tweak) {
    assert(t3f_key != NULL);
    assert(t3f_tweak != NULL);
    threefishSetKey(t3f_x, Threefish1024, t3f_key, t3f_tweak);
}

void t3f_encrypt(ThreefishKey_t *t3f_x, unsigned char *input,
                 unsigned char *output) {
    assert(t3f_x != NULL);
    assert(input != NULL);
    assert(output != NULL);
    threefishEncryptBlockBytes(t3f_x, input, output);
}

void t3f_decrypt(ThreefishKey_t *t3f_x, unsigned char *input,
                 unsigned char *output) {
    assert(t3f_x != NULL);
    assert(input != NULL);
    assert(output != NULL);
    threefishDecryptBlockBytes(t3f_x, input, output);
}
