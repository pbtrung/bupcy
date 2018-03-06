#include <stdio.h>

#include "CException/CException.h"
#include "utils/common.h"
#include "bupcy_cfg.h"
#include "argtable3/argtable3.h"
#include "repo/repo_stts.h"

// clang-format off

void show_general_error_msg(const char *hint_cmd) {
    show_error_msg("unrecognized option(s) or missing required option(s)",
                   hint_cmd);
}

void parse_help_version_cmd(int argc, char *argv[]) {
	struct arg_lit *help = arg_lit1("h", "help", "Show help and exit");
    struct arg_end *help_end = arg_end(10);
    void *help_argtbl[] = {
        help,
        help_end
    };
    check_log_exception(arg_nullcheck(help_argtbl) != 0, BUPCY_MALLOC_ERR);
    int help_argtbl_rc = arg_parse(argc, argv, help_argtbl);

    struct arg_lit *version = arg_lit1("v", "version", "Show version and exit");
    struct arg_end *version_end = arg_end(10);
    void *version_argtbl[] = {
        version,
        version_end
    };
    check_log_exception(arg_nullcheck(version_argtbl) != 0, BUPCY_MALLOC_ERR);
    int version_argtbl_rc = arg_parse(argc, argv, version_argtbl);

    // bupcy -h
    if (help_argtbl_rc == 0) {
        printf("DESCRIPTION");
        printf("\n");
        printf("    %s", "A local/cloud backup program in C, supporting compression, encryption, and deduplication");
        printf("\n\n");
        printf("USAGE");
        printf("\n");
        printf("    %s %s", PROGRAM_NAME, "[general options]");
        printf("\n");
        printf("    %s %s", PROGRAM_NAME, "[command] [command options] [arguments...]");
        printf("\n\n");
        printf("GENERAL OPTIONS");
        printf("\n");
        arg_print_glossary(stdout, help_argtbl, "    %-30s %s\n");
        arg_print_glossary(stdout, version_argtbl, "    %-30s %s\n");
        printf("\n");
        printf("COMMANDS");
        printf("\n");
        printf("    %-30s %s", "i, init", "Initialize a new repository");
        printf("\n");
        printf("    %-30s %s", "b, backup", "Backup to a repository");
        printf("\n\n");
        printf("NOTES");
        printf("\n");
        printf("    %s %-24s %s", PROGRAM_NAME, "[command] -h|--help", "Show help for command");
        printf("\n\n");

    // bupcy -v
    } else if (version_argtbl_rc == 0) {
        printf("%s %s\n\n", PROGRAM_NAME, BUPCY_VERSION);

    // error
    } else {
        show_general_error_msg(PROGRAM_NAME);
        check_exception(1, BUPCY_PARSE_CMDL_ERR);
    }

    arg_freetable(version_argtbl, sizeof(version_argtbl) / sizeof(version_argtbl[0]));
    arg_freetable(help_argtbl, sizeof(help_argtbl) / sizeof(help_argtbl[0]));
    return;
}

#define REG_EXTENDED 1
#define REG_ICASE (REG_EXTENDED << 1)

void parse_init_cmd(int argc, char *argv[], repo_stts_t *repo_stts) {
    bstring hint_cmd = bformat("%s %s", PROGRAM_NAME, "init");
    check_log_exception(hint_cmd == NULL, BUPCY_BSTRING_ERR);
    bstring config_dir_desc = bformat("%s %s%s", "Set path to bupcy configuration directory [default:", repo_stts->config_dir->data, "]");
    check_log_exception(config_dir_desc == NULL, BUPCY_BSTRING_ERR);

    struct arg_str *init_config_dir = arg_str0("c", "config-dir", "<path>", (char *)config_dir_desc->data);
    struct arg_rex *init_cmd = arg_rex1(NULL,  NULL, "init", NULL, REG_ICASE, "Initialize a new repository");
    struct arg_str *init_name = arg_str1("n", "name", "<name>", "REQUIRED. Set name of the new repository");
    struct arg_str *init_dest = arg_str1("d", "dest", "<URL>", "REQUIRED. Set remote/local path to backup to");
    struct arg_dbl *init_min_size = arg_dbl0("m", "min-size", "<size>", "Set minimum size of chunks in megabytes (MB) [default: 4MB]");
    struct arg_dbl *init_max_size = arg_dbl0("x", "max-size", "<size>", "Set maximum size of chunks in megabytes (MB) [default: 16MB]");
    struct arg_end *init_end = arg_end(10);
    void *init_argtbl[] = {
        init_cmd,
        init_name,
        init_dest,
        init_config_dir,
        init_min_size,
        init_max_size,
        init_end
    };
    check_log_exception(arg_nullcheck(init_argtbl) != 0, BUPCY_MALLOC_ERR);
    int init_argtbl_rc = arg_parse(argc, argv, init_argtbl);

    struct arg_rex *init_help_cmd = arg_rex1(NULL,  NULL, "init", NULL, REG_ICASE, "Initialize a new repository");
    struct arg_end *init_help_end = arg_end(10);
    struct arg_lit *init_help = arg_lit1("h", "help", "Show help and exit");
    void *init_help_argtbl[] = {
        init_help_cmd,
        init_help,
        init_help_end
    };
    check_log_exception(arg_nullcheck(init_help_argtbl) != 0, BUPCY_MALLOC_ERR);
    int init_help_argtbl_rc = arg_parse(argc, argv, init_help_argtbl);

    struct arg_rex *i_cmd = arg_rex1(NULL,  NULL, "i", NULL, REG_ICASE, "Initialize a new repository");
    void *i_argtbl[] = {
        i_cmd,
        init_name,
        init_dest,
        init_config_dir,
        init_min_size,
        init_max_size,
        init_end
    };
    check_log_exception(arg_nullcheck(i_argtbl) != 0, BUPCY_MALLOC_ERR);
    int i_argtbl_rc = arg_parse(argc, argv, i_argtbl);

    struct arg_rex *i_help_cmd = arg_rex1(NULL,  NULL, "i", NULL, REG_ICASE, "Initialize a new repository");
    void *i_help_argtbl[] = {
        i_help_cmd,
        init_help,
        init_help_end
    };
    check_log_exception(arg_nullcheck(i_help_argtbl) != 0, BUPCY_MALLOC_ERR);
    int i_help_argtbl_rc = arg_parse(argc, argv, i_help_argtbl);

    // bupcy init -h
    if (init_help_argtbl_rc == 0 || i_help_argtbl_rc == 0) {
        printf("DESCRIPTION");
        printf("\n");
        printf("    %s %s|%s -- %s", PROGRAM_NAME, i_cmd->hdr.datatype, init_cmd->hdr.datatype, init_cmd->hdr.glossary);
        printf("\n\n");
        printf("USAGE");
        printf("\n");
        printf("    %s", PROGRAM_NAME);
        arg_print_syntaxv(stdout, i_help_argtbl, "\n");
        printf("    %s", PROGRAM_NAME);
        arg_print_syntax(stdout, i_argtbl, "\n");
        printf("    %s", PROGRAM_NAME);
        arg_print_syntaxv(stdout, init_help_argtbl, "\n");
        printf("    %s", PROGRAM_NAME);
        arg_print_syntax(stdout, init_argtbl, "\n\n");
        printf("OPTIONS");
        printf("\n");
        printf("    -%s, --%-19s %s", init_help->hdr.shortopts, init_help->hdr.longopts, init_help->hdr.glossary);
        printf("\n");
        printf("    -%s, --%-19s %s", init_name->hdr.shortopts, init_name->hdr.longopts, init_name->hdr.glossary);
        printf("\n");
        printf("    -%s, --%-19s %s", init_dest->hdr.shortopts, init_dest->hdr.longopts, init_dest->hdr.glossary);
        printf("\n");
        printf("    -%s, --%-19s %s", init_config_dir->hdr.shortopts, init_config_dir->hdr.longopts, init_config_dir->hdr.glossary);
        printf("\n");
        printf("    -%s, --%-19s %s", init_min_size->hdr.shortopts, init_min_size->hdr.longopts, init_min_size->hdr.glossary);
        printf("\n");
        printf("    -%s, --%-19s %s", init_max_size->hdr.shortopts, init_max_size->hdr.longopts, init_max_size->hdr.glossary);
        printf("\n\n");
        printf("NOTES");
        printf("\n");
        printf("    %s", "<size> is a number without unit (e.g., 2, 2.5, etc.)");
        printf("\n");
        printf("      * %s", "Minimum allowable size is 2MB");
        printf("\n");
        printf("      * %s", "Maximum allowable size is 32MB");
        printf("\n\n");
        printf("    %s", "<URL> must have one of the following formats:");
        printf("\n");
        printf("      * %s", "Local storage:      lol://path/to/backup/directory");
        printf("\n");
        printf("      * %s", "FTP:                ftp://path/to/backup/directory");
        printf("\n");
        printf("      * %s", "Google Drive:       gdr://path/to/backup/directory");
        printf("\n");
        printf("      * %s", "Amazon S3:          as3://path/to/backup/directory");
        printf("\n");
        printf("      * %s", "Microsoft OneDrive: one://path/to/backup/directory");
        printf("\n");
        printf("      * %s", "Dropbox:            dbx://path/to/backup/directory");
        printf("\n\n");

    // bupcy init
    } else if (init_argtbl_rc == 0 || i_argtbl_rc == 0) {
        repo_stts->name = bfromcstr(init_name->sval[0]);
        repo_stts->dest = bfromcstr(init_dest->sval[0]);
        if (init_config_dir->count > 0) {
            int rc = bassigncstr(repo_stts->config_dir, init_config_dir->sval[0]);
            check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
        }
        if (init_min_size->count > 0) {
            double val = init_min_size->dval[0] * MEGABYTE;
            repo_stts_check_size(val, BUPCY_MIN_CHUNK_SIZE_ERR, (char *)hint_cmd->data);
            repo_stts->min_size = (uint32_t)val;
        }
        if (init_max_size->count > 0) {
            double val = init_max_size->dval[0] * MEGABYTE;
            repo_stts_check_size(val, BUPCY_MAX_CHUNK_SIZE_ERR, (char *)hint_cmd->data);
            repo_stts->max_size = (uint32_t)val;
        }

    } else {
        show_general_error_msg((char *)hint_cmd->data);
        check_exception(1, BUPCY_PARSE_CMDL_ERR);
    }

    bupcy_free(i_help_cmd);
    bupcy_free(i_cmd);
    arg_freetable(init_help_argtbl, sizeof(init_help_argtbl) / sizeof(init_help_argtbl[0]));
    arg_freetable(init_argtbl, sizeof(init_argtbl) / sizeof(init_argtbl[0]));
    bdestroy(config_dir_desc);
    bdestroy(hint_cmd);
    return;
}

// clang-format on

#if defined(_WIN32)
int wmain(int argc, wchar_t *wargv[]) {
#else
int main(int argc, char *argv[]) {
#endif
    rc_t rc = BUPCY_SUCCESS;
    CEXCEPTION_T e;

    log_set_level(LOG_FATAL);

#if defined(_WIN32)
    char **argv = NULL;
    Try {
        argv = bupcy_malloc(argc * sizeof(char *));
        for (int i = 0; i < argc; ++i) {
            argv[i] = bupcy_shorten(wargv[i]);
            check_exception(argv[i] == NULL, BUPCY_SHORTEN_ERR);
        }
    }
    Catch(e) {
    	log_rc_msg(e);
		exit(e);
    }
#endif
    
    Try {
        if (argc == 1) {
        	show_general_error_msg(PROGRAM_NAME);
        	check_exception(1, BUPCY_PARSE_CMDL_ERR);
    	} else if (argc == 2) {
    		parse_help_version_cmd(argc, argv);
    	} else {
            if (strcmp(argv[1], "init") == 0 || strcmp(argv[1], "i") == 0) {
                bstring hint_cmd = bformat("%s %s", PROGRAM_NAME, "init");
                check_log_exception(hint_cmd == NULL, BUPCY_BSTRING_ERR);
                repo_stts_t *repo_stts = repo_stts_init();
                parse_init_cmd(argc, argv, repo_stts);
                repo_stts_validate(repo_stts, (char *)hint_cmd->data);
                repo_stts_free(repo_stts);
                bdestroy(hint_cmd);
            }
    	}
    }
    Catch(e) {
        log_rc_msg(e);
		exit(e);
    }

#if defined(_WIN32)
    bupcy_free_arr(argc, argv);
#endif

    return rc;
}
