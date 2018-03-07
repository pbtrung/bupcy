#include "utils/common.h"
#include "repo/repo_stts.h"
#include "utils/utils.h"

repo_stts_t *repo_stts_init() {
    repo_stts_t *repo_stts = bupcy_malloc(sizeof(repo_stts_t));

    repo_stts->min_size = 4 * MEGABYTE;
    repo_stts->max_size = 16 * MEGABYTE;
    repo_stts->name = NULL;
    repo_stts->dest = NULL;
    repo_stts->config_dir_exists = false;
    repo_stts->config_dir = bupcy_get_default_config_dir();

    return repo_stts;
}

void repo_stts_free(repo_stts_t *repo_stts) {
    bdestroy(repo_stts->config_dir);
    bdestroy(repo_stts->name);
    bdestroy(repo_stts->dest);
    bupcy_free(repo_stts);
}

void repo_stts_check_size(double val, rc_t rc, const char *hint_cmd) {
    if (val > MAX_CHUNK_SIZE || val < MIN_CHUNK_SIZE) {
        show_error_msg("size must be between 2MB and 32MB", hint_cmd);
        check_exception(1, rc);
    }
}

bool repo_stts_check_name(repo_stts_t *repo_stts) {
    bool b = false;
    return b;
}

void repo_stts_validate(repo_stts_t *repo_stts, const char *hint_cmd) {
    if (repo_stts->min_size >= repo_stts->max_size) {
        show_error_msg("minimum size must be smaller than maximum size", hint_cmd);
        check_exception(1, BUPCY_REPO_STTS_VALIDATE_ERR);
    }
    if (bupcy_dir_exists((char *)repo_stts->config_dir->data) == false) {
        bool b = bupcy_mkdir_recursive((char *)repo_stts->config_dir->data);
        check_log_exception(b == false, BUPCY_MKDIR_ERR);
    } else {
        bool b = repo_stts_check_name(repo_stts);
        check_log_exception(b == true, BUPCY_REPO_NAME_EXISTS_ERR);
    }
}