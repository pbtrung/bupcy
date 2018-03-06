#include <assert.h>

#include "crypto/skein.h"
#include "skein3fish/skeinApi.h"
#include "utils/common.h"

void skein_hash(const unsigned char *input, size_t in_len,
                unsigned char *output) {
    assert(input != NULL);
    assert(output != NULL);
    assert(in_len > 0);

    rc_t rc = BUPCY_SUCCESS;
    SkeinCtx_t *skein_x = bupcy_malloc(sizeof(SkeinCtx_t));

    rc = skeinCtxPrepare(skein_x, Skein512);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinInit(skein_x, Skein512);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinUpdate(skein_x, input, in_len);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinFinal(skein_x, output);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    bupcy_free(skein_x);
}

void skein_mac(const unsigned char *skein_mac_key, const unsigned char *input,
               size_t in_len, unsigned char *output) {
    assert(input != NULL);
    assert(output != NULL);
    assert(skein_mac_key != NULL);
    assert(in_len > 0);

    rc_t rc = BUPCY_SUCCESS;
    SkeinCtx_t *skein_x = bupcy_malloc(sizeof(SkeinCtx_t));

    rc = skeinCtxPrepare(skein_x, Skein512);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinMacInit(skein_x, skein_mac_key, SKEIN_MAC_KEY_LEN, Skein512);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinUpdate(skein_x, input, in_len);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinFinal(skein_x, output);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    bupcy_free(skein_x);
}

void skein_mac_init(SkeinCtx_t *skein_x, const unsigned char *skein_mac_key) {
    assert(skein_mac_key != NULL);
    assert(skein_x != NULL);

    rc_t rc = BUPCY_SUCCESS;

    rc = skeinCtxPrepare(skein_x, Skein512);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    rc = skeinMacInit(skein_x, skein_mac_key, SKEIN_MAC_KEY_LEN, Skein512);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);
}

void skein_mac_update(SkeinCtx_t *skein_x, const unsigned char *input,
                      size_t in_len) {
    assert(input != NULL);
    assert(skein_x != NULL);
    assert(in_len > 0);

    rc_t rc = BUPCY_SUCCESS;
    rc = skeinUpdate(skein_x, input, in_len);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);
}

void skein_mac_final(SkeinCtx_t *skein_x, unsigned char *output) {
    assert(skein_x != NULL);
    assert(output != NULL);

    rc_t rc = BUPCY_SUCCESS;
    rc = skeinFinal(skein_x, output);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_SKEIN_ERR);

    skeinReset(skein_x);
}
