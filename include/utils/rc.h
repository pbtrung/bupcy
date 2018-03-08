#ifndef RC_H
#define RC_H

enum rc_t {
    BUPCY_SUCCESS = 0,
    BUPCY_SKEIN_ERR,
    BUPCY_ARGON2_ERR,
    BUPCY_CTR_HC256_USED_ERR,
    BUPCY_MALLOC_ERR,
    BUPCY_CALLOC_ERR,
    BUPCY_REALLOC_ERR,
    BUPCY_BASE58_ERR,
    BUPCY_SHORTEN_ERR,
    BUPCY_WIDEN_ERR,
    BUPCY_PARSE_CMDL_ERR,
    BUPCY_ENV_VAR_ERR,
    BUPCY_BSTRING_ERR,
    BUPCY_MAX_CHUNK_SIZE_ERR,
    BUPCY_MIN_CHUNK_SIZE_ERR,
    BUPCY_REPO_STTS_VALIDATE_ERR,
    BUPCY_MKDIR_ERR,
    BUPCY_REPO_NAME_EXISTS_ERR,
    BUPCY_FILE_ERR,
};
typedef enum rc_t rc_t;

const char *rc_msg(rc_t rc);
#define log_rc_msg(rc) log_error("%s", rc_msg(rc))

#endif // RC_H
