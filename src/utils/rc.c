#include "utils/common.h"

const char *rc_msg(rc_t rc) {
    switch (rc) {
    case BUPCY_SUCCESS:
        return "BUPCY_SUCCESS";
    case BUPCY_SKEIN_ERR:
        return "BUPCY_SKEIN_ERR";
    case BUPCY_ARGON2_ERR:
        return "BUPCY_ARGON2_ERR";
    case BUPCY_CTR_HC256_USED_ERR:
        return "BUPCY_CTR_HC256_USED_ERR";
    case BUPCY_MALLOC_ERR:
        return "BUPCY_MALLOC_ERR";
    case BUPCY_CALLOC_ERR:
        return "BUPCY_CALLOC_ERR";
    case BUPCY_REALLOC_ERR:
        return "BUPCY_REALLOC_ERR";
    case BUPCY_BASE58_ERR:
        return "BUPCY_BASE58_ERR";
    case BUPCY_SHORTEN_ERR:
        return "BUPCY_SHORTEN_ERR";
    case BUPCY_WIDEN_ERR:
        return "BUPCY_WIDEN_ERR";
    case BUPCY_PARSE_CMDL_ERR:
        return "BUPCY_PARSE_CMDL_ERR";
    case BUPCY_ENV_VAR_ERR:
        return "BUPCY_ENV_VAR_ERR";
    case BUPCY_BSTRING_ERR:
        return "BUPCY_BSTRING_ERR";
    case BUPCY_MAX_CHUNK_SIZE_ERR:
        return "BUPCY_MAX_CHUNK_SIZE_ERR";
    case BUPCY_MIN_CHUNK_SIZE_ERR:
        return "BUPCY_MIN_CHUNK_SIZE_ERR";
    case BUPCY_REPO_STTS_VALIDATE_ERR:
        return "BUPCY_REPO_STTS_VALIDATE_ERR";
    case BUPCY_MKDIR_ERR:
        return "BUPCY_MKDIR_ERR";
    case BUPCY_REPO_NAME_EXISTS_ERR:
        return "BUPCY_REPO_NAME_EXISTS_ERR";
    case BUPCY_FILE_ERR:
        return "BUPCY_FILE_ERR";
    case BUPCY_PARSE_TOML_ERR:
        return "BUPCY_PARSE_TOML_ERR";
    default:
        return "Unknown return code";
    }
}

