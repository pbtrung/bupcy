#include "utils/common.h"
#include "repo/repo_init.h"
#include "utils/utils.h"
#include "utils/base58.h"
#include "randombytes/randombytes.h"

repo_secrets_t *repo_init_make_secrets() {
    repo_secrets_t *repo_secrets = bupcy_malloc(sizeof(repo_secrets_t));
    char *password = bupcy_malloc(REPO_PASSWORD_LEN);
    char *salt = bupcy_malloc(REPO_SALT_LEN);
    repo_secrets->bs58_password = bupcy_malloc(base58_encode_size(REPO_PASSWORD_LEN) + 1);
    repo_secrets->bs58_salt = bupcy_malloc(base58_encode_size(REPO_SALT_LEN) + 1);

    randombytes(password, REPO_PASSWORD_LEN);
    randombytes(salt, REPO_SALT_LEN);
    rc_t rc = BUPCY_SUCCESS;
    rc = base58_encode(password, REPO_PASSWORD_LEN, repo_secrets->bs58_password);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BASE58_ERR);
    rc = base58_encode(salt, REPO_SALT_LEN, repo_secrets->bs58_salt);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BASE58_ERR);

    bupcy_free(password);
    bupcy_free(salt);
    return repo_secrets;
}

void repo_init_free_secrets(repo_secrets_t *repo_secrets) {
    bupcy_free(repo_secrets->bs58_password);
    bupcy_free(repo_secrets->bs58_salt);
    bupcy_free(repo_secrets);
}

bool repo_init(repo_stts_t *repo_stts) {
    bool b = true;

    bstring conf_path = repo_stts_get_conf_file_path(repo_stts);

    FILE *fp = bupcy__fopen((char *)conf_path->data, "ab");
    check_log_exception(fp == NULL, BUPCY_FILE_ERR);
    
    repo_secrets_t *repo_secrets = repo_init_make_secrets();
    bstring buf = bformat("[%s]\n"
                          "password = %s\n"
                          "salt = %s\n"
                          "dest = %s\n"
                          "min_size = %d\n"
                          "max_size = %d\n"
                          "\n",  
                          repo_stts->name->data,
                          repo_secrets->bs58_password,
                          repo_secrets->bs58_salt,
                          repo_stts->dest->data,
                          repo_stts->min_size,
                          repo_stts->max_size);
    check_log_exception(buf == NULL, BUPCY_FILE_ERR);

    fwrite(buf->data, sizeof(char), buf->slen, fp);
    fclose(fp);
    
    repo_init_free_secrets(repo_secrets);
    bdestroy(buf);
    bdestroy(conf_path);
    return b;
}