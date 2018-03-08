#ifndef REPO_STTS_H
#define REPO_STTS_H

#include <stdint.h>

#include "bstrlib/bstrlib.h"
#include "utils/common.h"

#define MEGABYTE (1024 * 1024)
#define MAX_CHUNK_SIZE (32 * MEGABYTE)
#define MIN_CHUNK_SIZE (2 * MEGABYTE)

struct repo_stts_t {
    bstring name;
    bstring dest;
    bstring config_dir;
    bool config_dir_exists;
    bool conf_file_exists;
    uint32_t min_size;
    uint32_t max_size;
};
typedef struct repo_stts_t repo_stts_t;

repo_stts_t *repo_stts_init();
void repo_stts_free(repo_stts_t *repo_stts);
void repo_stts_validate(repo_stts_t *repo_stts, const char *hint_cmd);
void repo_stts_check_size(double val, rc_t rc, const char *hint_cmd);
bool repo_stts_check_name(repo_stts_t *repo_stts);
bstring repo_stts_get_conf_file_path(repo_stts_t *repo_stts);

#endif // REPO_STTS_H
