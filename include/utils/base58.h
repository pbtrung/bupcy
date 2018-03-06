#ifndef UTILS_BASE58_H
#define UTILS_BASE58_H

#include <stdint.h>
#include <stdlib.h>

#include "utils/common.h"

size_t base58_encode_size(int32_t in_len);
rc_t base58_encode(const void *input, size_t in_len, char *output);

size_t base58_decode_size(int32_t in_len);
rc_t base58_decode(const char *input, size_t in_len, char *output);

#endif // UTILS_BASE58_H
