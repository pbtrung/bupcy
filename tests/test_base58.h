#include "greatest.h"
#include "randombytes/randombytes.h"
#include "utils/base58.h"

TEST test_base58_enc_dec() {
    rc_t rc = BUPCY_SUCCESS;

    size_t buf_len = 64;
    char *buf = malloc(buf_len);
    size_t enc_len = base58_encode_size(buf_len) + 1;
    char *enc = malloc(enc_len);
    size_t dec_len = buf_len;
    char *dec = malloc(dec_len + 1);

    for (int i = 0; i < 1; ++i) {
        randombytes(buf, buf_len);
        rc = base58_encode(buf, buf_len, enc);
        ASSERT_EQ(rc, BUPCY_SUCCESS);
        // printf("%s\n", enc);
        rc = base58_decode(enc, enc_len, dec);
        ASSERT_EQ(rc, BUPCY_SUCCESS);
        rc = memcmp(buf, dec, buf_len);
        ASSERT_EQ(rc, BUPCY_SUCCESS);
    }

    free(buf);
    free(enc);
    free(dec);

    PASS();
}

SUITE(test_base58) {
    RUN_TEST(test_base58_enc_dec);
}
