#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <wchar.h>

#include "bstrlib/bstrlib.h"
#include "utils/common.h"

#if defined(_WIN32)
	#if !defined(NOMINMAX)
		#define NOMINMAX
	#endif
	#if !defined(WIN32_LEAN_AND_MEAN)
		#define WIN32_LEAN_AND_MEAN
	#endif
	#if !defined(VC_EXTRALEAN)
		#define VC_EXTRALEAN
	#endif
	#if !defined(UNICODE)
		#define UNICODE
	#endif
	#include <windows.h>
	#include "dirent/dirent.h"

	#pragma comment(lib, "kernel32.lib")
#else
	#include <dirent.h>
#endif

#if defined(_WIN32)
    #define BUPCY_PATH_SEPARATOR '\\'
	wchar_t *stb_from_utf8(wchar_t *buffer, const char *ostr, int n);
	char *stb_to_utf8(char *buffer, const wchar_t *str, int n);
	wchar_t *bupcy_widen(const char *str);
	char *bupcy_shorten(const wchar_t *str);
#else
    #define BUPCY_PATH_SEPARATOR '/'
#endif

void *bupcy_malloc(size_t n);
void *bupcy_calloc(size_t num, size_t size);
void *bupcy_realloc(void *ptr, size_t size);
void bupcy_free_arr(int arr_len, void *arr[]);

bstring bupcy_get_env_var(const char *env_var_name);
bstring bupcy_get_home_dir();
bstring bupcy_get_default_config_dir();

void show_hint(const char *hint_cmd);
void show_error_msg(const char *msg, const char *hint_cmd);

bool bupcy_dir_exists(const char *path);
bool bupcy_file_exists(const char *path);
bool bupcy_mkdir_recursive(char *path);
void stb_fixpath(char *path);

#endif // UTILS_H
