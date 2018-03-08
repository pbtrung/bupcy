#ifndef REPO_INIT_H
#define REPO_INIT_H

#include "bstrlib/bstrlib.h"
#include "utils/common.h"
#include "repo/repo_stts.h"

#define REPO_PASSWORD_LEN 128U
#define REPO_SALT_LEN 32U

struct repo_secrets_t {
	char *bs58_password;
	char *bs58_salt;
};
typedef struct repo_secrets_t repo_secrets_t;

bool repo_init(repo_stts_t *repo_stts);
repo_secrets_t *repo_init_make_secrets();
void repo_init_free_secrets(repo_secrets_t *repo_secrets);

#endif // REPO_INIT_H
