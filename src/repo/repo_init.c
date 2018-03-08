#include "utils/common.h"
#include "repo/repo_init.h"
#include "utils/utils.h"

bool repo_init(repo_stts_t *repo_stts) {
    bool b = true;

    bstring conf_path = repo_stts_get_conf_file_path(repo_stts);

    FILE *fp = bupcy__fopen((char *)conf_path->data, "ab");
    check_log_exception(fp == NULL, BUPCY_FILE_ERR);
    
    bstring buf = bformat("[%s]\n"
                          "dest = %s\n"
                          "min_size = %d\n"
                          "max_size = %d\n"
                          "\n",  
                          repo_stts->name->data,
                          repo_stts->dest->data,
                          repo_stts->min_size,
                          repo_stts->max_size);
    check_log_exception(buf == NULL, BUPCY_FILE_ERR);

    fwrite(buf->data, sizeof(char), buf->slen, fp);
    fclose(fp);
    
    bdestroy(buf);
    bdestroy(conf_path);
    return b;
}