#include "utils/common.h"
#include "repo/repo_stts.h"
#include "utils/utils.h"
#include "toml/toml.h"

repo_stts_t *repo_stts_init() {
    repo_stts_t *repo_stts = bupcy_malloc(sizeof(repo_stts_t));

    repo_stts->min_size = 4 * MEGABYTE;
    repo_stts->max_size = 16 * MEGABYTE;
    repo_stts->name = NULL;
    repo_stts->dest = NULL;
    repo_stts->config_dir_exists = false;
    repo_stts->conf_file_exists = false;
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

bstring repo_stts_get_conf_file_path(repo_stts_t *repo_stts) {
    stb_fixpath((char *)repo_stts->config_dir->data);
    if (repo_stts->config_dir->data[repo_stts->config_dir->slen - 1] == '/') {
        int rc = bdelete(repo_stts->config_dir, repo_stts->config_dir->slen - 1, 1);
        check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
    }
    bstring conf_path = bformat("%s%c%s", repo_stts->config_dir->data, '/', "bupcy.conf");
    check_log_exception(conf_path == NULL, BUPCY_BSTRING_ERR);
    return conf_path;
}

bool repo_stts_check_name(repo_stts_t *repo_stts) {
    bool b = false;

    bstring conf_path = repo_stts_get_conf_file_path(repo_stts);
    if (bupcy_file_exists((char *)conf_path->data) == false) {
        FILE *fp = bupcy__fopen((char *)conf_path->data, "ab+");
        check_log_exception(fp == NULL, BUPCY_FILE_ERR);
        fclose(fp);
    } else {
        FILE *fp = bupcy__fopen((char *)conf_path->data, "rb");
        check_log_exception(fp == NULL, BUPCY_FILE_ERR);
        char errbuf[256];
        toml_table_t *conf = NULL;
        conf = toml_parse_file(fp, errbuf, sizeof(errbuf));
        fclose(fp);
        check_log_exception(conf == NULL, BUPCY_PARSE_TOML_ERR);
        toml_table_t *repo = NULL;
        repo = toml_table_in(conf, (char *)repo_stts->name->data);
        if (repo != NULL) {
            b = true;
        }
        toml_free(conf);
    }

    bdestroy(conf_path);
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
        repo_stts->config_dir_exists = true;
    }
    if (repo_stts_check_name(repo_stts) == true) {
        show_error_msg("repository name has already existed", hint_cmd);
        check_log_exception(1, BUPCY_REPO_STTS_VALIDATE_ERR);
    }
}