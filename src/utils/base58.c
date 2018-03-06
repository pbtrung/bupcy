#include <assert.h>
#include <math.h>

#include "base58/base58.h"
#include "utils/base58.h"

size_t base58_encode_size(int32_t in_len) {
    assert(in_len > 0);
    return (size_t)ceil(in_len * 1.375);
}
// output_len = base58_encode_size(in_len) + 1;
rc_t base58_encode(const void *input, size_t in_len, char *output) {
    assert(in_len > 0);
    assert(input != NULL);
    assert(output != NULL);

    rc_t rc = BUPCY_SUCCESS;
    size_t out_len = base58_encode_size(in_len) + 1;
    size_t in_out_len = out_len;
    bool b = b58enc(output, &in_out_len, input, in_len);
    if (b == false) {
        rc = BUPCY_BASE58_ERR;
        goto exit;
    }

    while (in_out_len < out_len) {
        output[in_out_len - 1] = '0';
        in_out_len++;
    }
    output[in_out_len - 1] = '\0';

exit:
    return rc;
}

size_t base58_decode_size(int32_t in_len) {
    assert(in_len > 0);
    return (size_t)floor(in_len / 1.375);
}
// output_len = base58_decode_size(in_len) + 1;
// in_len = strlen(input) + 1;
rc_t base58_decode(const char *input, size_t in_len, char *output) {
    assert(in_len > 0);
    assert(input != NULL);
    assert(output != NULL);

    rc_t rc = BUPCY_SUCCESS;
    size_t out_len = base58_decode_size(in_len - 1);
    in_len -= 1;
    while (input[in_len - 1] == '0') {
        in_len--;
    }
    bool b = b58tobin(output, &out_len, input, in_len);
    if (b == false) {
        rc = BUPCY_BASE58_ERR;
    }
    return rc;
}
