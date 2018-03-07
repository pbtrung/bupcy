#include <assert.h>
#include <string.h>

#include "bupcy_cfg.h"
#include "utils/common.h"
#include "utils/utils.h"

#if !defined(_WIN32)
    #include <errno.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

wchar_t *stb_from_utf8(wchar_t *buffer, const char *ostr, int n) {
    unsigned char *str = (unsigned char *)ostr;
    uint32_t c;
    int i = 0;
    --n;
    while (*str) {
        if (i >= n)
            return NULL;
        if (!(*str & 0x80))
            buffer[i++] = *str++;
        else if ((*str & 0xe0) == 0xc0) {
            if (*str < 0xc2)
                return NULL;
            c = (*str++ & 0x1f) << 6;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            buffer[i++] = c + (*str++ & 0x3f);
        } else if ((*str & 0xf0) == 0xe0) {
            if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf))
                return NULL;
            if (*str == 0xed && str[1] > 0x9f)
                return NULL; // str[1] < 0x80 is checked below
            c = (*str++ & 0x0f) << 12;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            buffer[i++] = c + (*str++ & 0x3f);
        } else if ((*str & 0xf8) == 0xf0) {
            if (*str > 0xf4)
                return NULL;
            if (*str == 0xf0 && (str[1] < 0x90 || str[1] > 0xbf))
                return NULL;
            if (*str == 0xf4 && str[1] > 0x8f)
                return NULL; // str[1] < 0x80 is checked below
            c = (*str++ & 0x07) << 18;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f) << 12;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f) << 6;
            if ((*str & 0xc0) != 0x80)
                return NULL;
            c += (*str++ & 0x3f);
            // utf-8 encodings of values used in surrogate pairs are invalid
            if ((c & 0xFFFFF800) == 0xD800)
                return NULL;
            if (c >= 0x10000) {
                c -= 0x10000;
                if (i + 2 > n)
                    return NULL;
                buffer[i++] = 0xD800 | (0x3ff & (c >> 10));
                buffer[i++] = 0xDC00 | (0x3ff & (c));
            }
        } else
            return NULL;
    }
    buffer[i] = 0;
    return buffer;
}

char *stb_to_utf8(char *buffer, const wchar_t *str, int n) {
    int i = 0;
    --n;
    while (*str) {
        if (*str < 0x80) {
            if (i + 1 > n)
                return NULL;
            buffer[i++] = (char)*str++;
        } else if (*str < 0x800) {
            if (i + 2 > n)
                return NULL;
            buffer[i++] = 0xc0 + (*str >> 6);
            buffer[i++] = 0x80 + (*str & 0x3f);
            str += 1;
        } else if (*str >= 0xd800 && *str < 0xdc00) {
            uint32_t c;
            if (i + 4 > n)
                return NULL;
            c = ((str[0] - 0xd800) << 10) + ((str[1]) - 0xdc00) + 0x10000;
            buffer[i++] = 0xf0 + (c >> 18);
            buffer[i++] = 0x80 + ((c >> 12) & 0x3f);
            buffer[i++] = 0x80 + ((c >> 6) & 0x3f);
            buffer[i++] = 0x80 + ((c)&0x3f);
            str += 2;
        } else if (*str >= 0xdc00 && *str < 0xe000) {
            return NULL;
        } else {
            if (i + 3 > n)
                return NULL;
            buffer[i++] = 0xe0 + (*str >> 12);
            buffer[i++] = 0x80 + ((*str >> 6) & 0x3f);
            buffer[i++] = 0x80 + ((*str) & 0x3f);
            str += 1;
        }
    }
    buffer[i] = 0;
    return buffer;
}

wchar_t *bupcy_widen(const char *str) {
    assert(str != NULL);
    int len = (strlen(str) + 1) * 4;
    wchar_t *buffer = bupcy_malloc(len * sizeof(char));
    return stb_from_utf8(buffer, str, len);
}

char *bupcy_shorten(const wchar_t *str) {
    assert(str != NULL);
    int len = (wcslen(str) + 1) * 4;
    char *buffer = bupcy_malloc(len * sizeof(char));
    return stb_to_utf8(buffer, str, len);
}

void *bupcy_malloc(size_t n) {
    assert(n > 0);
    void *x = malloc(n);
    check_log_exception(x == NULL, BUPCY_MALLOC_ERR);
    return x;
}

void *bupcy_calloc(size_t num, size_t size) {
    assert(num > 0);
    assert(size > 0);
    void *x = calloc(num, size);
    check_log_exception(x == NULL, BUPCY_CALLOC_ERR);
    return x;
}

void *bupcy_realloc(void *ptr, size_t size) {
    assert(size > 0);
    void *x = realloc(ptr, size);
    check_log_exception(x == NULL, BUPCY_REALLOC_ERR);
    return x;
}

void bupcy_free_arr(int arr_len, void *arr[]) {
    if (arr != NULL) {
        for (int i = 0; i < arr_len; ++i) {
            bupcy_free(arr[i]);
        }
        bupcy_free(arr);
    }
}

bstring bupcy_get_env_var(const char *env_var_name) {
    assert(env_var_name != NULL);
    bstring env_var = NULL;

#if defined(_WIN32)
    size_t buf_size = 64;
    wchar_t *buf = bupcy_malloc(buf_size * 4);
    wchar_t *name = bupcy_widen(env_var_name);
    check_log_exception(name == NULL, BUPCY_WIDEN_ERR);

    size_t n = GetEnvironmentVariableW(name, buf, buf_size);
    check_log_exception(n == 0 && GetLastError() == 203, BUPCY_ENV_VAR_ERR);

    if (n >= buf_size) {
        size_t oldn = n;
        bupcy_realloc(buf, (n + 1) * 4);
        n = GetEnvironmentVariableW(name, buf, n);
        // The size may have changed
        check_log_exception(n > oldn, BUPCY_ENV_VAR_ERR);
    }

    char *tmp_env_var = bupcy_shorten(buf);
    check_log_exception(tmp_env_var == NULL, BUPCY_SHORTEN_ERR);
    env_var = bfromcstr(tmp_env_var);

    bupcy_free(buf);
    bupcy_free(name);
    bupcy_free(tmp_env_var);
#else
    env_var = bfromcstr(getenv(env_var_name));
#endif

    check_log_exception(env_var == NULL, BUPCY_BSTRING_ERR);
    return env_var;
}

bstring bupcy_get_home_dir() {
    rc_t rc = BUPCY_SUCCESS;
    bstring home_dir = NULL;

#if defined(_WIN32)
    char env_var_name[] = "USERPROFILE";
#else
    char env_var_name[] = "HOME";
#endif

    home_dir = bupcy_get_env_var(env_var_name);
    rc = bconchar(home_dir, BUPCY_PATH_SEPARATOR);
    check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);

    return home_dir;
}

bstring bupcy_get_default_config_dir() {
    bstring home_dir = bupcy_get_home_dir();
    bstring config_dir =
        bformat("%s%s%c", home_dir->data, ".bupcy", BUPCY_PATH_SEPARATOR);
    check_log_exception(config_dir == NULL, BUPCY_BSTRING_ERR);

    bdestroy(home_dir);
    return config_dir;
}

void show_hint(const char *hint_cmd) {
    printf("%s: %s -h for help\n\n", PROGRAM_NAME, hint_cmd);
}

void show_error_msg(const char *msg, const char *hint_cmd) {
    printf("%s: %s\n", PROGRAM_NAME, msg);
    show_hint(hint_cmd);
}

bool bupcy_dir_exists(const char *path) {
    if (path == NULL) {
        return false;
    }

    DIR *dir;
    bool exists = false;

    dir = opendir(path);

    if (dir != NULL) {
        exists = true;
        (void)closedir(dir);
    }

    return exists;
}

void stb_fixpath(char *path) {
    for (; *path; ++path)
        if (*path == '\\')
            *path = '/';
}

bool bupcy_mkdir_recursive(char *path) {
    assert(path != NULL);
    struct bstrList *parts = NULL;
    bool ret = true;
    int i = 0;
    bstring dir_path = bfromcstr("");
    rc_t rc = BUPCY_SUCCESS;

    stb_fixpath(path);
    bstring tmp_path = bfromcstr(path);
    parts = bsplit(tmp_path, '/');
    check_log_exception(parts == NULL, BUPCY_BSTRING_ERR);
    bdestroy(tmp_path);

#if defined(_WIN32)
    if (bstrchr(parts->entry[0], ':') != BSTR_ERR) {
        i++;
        rc = bconcat(dir_path, parts->entry[0]);
        check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
        rc = bconchar(dir_path, BUPCY_PATH_SEPARATOR);
        check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
    }
#else
    if (strcmp((char *)parts->entry[0]->data, "") == 0) {
        rc = bconchar(dir_path, BUPCY_PATH_SEPARATOR);
        check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
    }
#endif

    for (; i < parts->qty; ++i) {
        if (parts->entry[i]->data == NULL || *(parts->entry[i]->data) == '\0') {
            continue;
        }
        rc = bconcat(dir_path, parts->entry[i]);
        check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
        rc = bconchar(dir_path, BUPCY_PATH_SEPARATOR);
        check_log_exception(rc != BUPCY_SUCCESS, BUPCY_BSTRING_ERR);
#if defined(_WIN32)
        wchar_t *wpath = bupcy_widen((char *)dir_path->data);
        check_log_exception(wpath == NULL, BUPCY_WIDEN_ERR);
        if (CreateDirectoryW(wpath, NULL) == FALSE) {
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                ret = false;
            }
        }
        bupcy_free(wpath);
        if (ret == false) {
            goto exit;
        }
#else
        if (mkdir((char *)dir_path->data, 0774) != 0) {
            if (errno != EEXIST) {
                ret = false;
                goto exit;
            }
        }
#endif
    }

exit:
    bstrListDestroy(parts);
    bdestroy(dir_path);
    return ret;
}