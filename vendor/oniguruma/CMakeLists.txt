set(PACKAGE onig)
set(PACKAGE_VERSION "6.7.1")

set(USE_COMBINATION_EXPLOSION_CHECK 0)
set(USE_CRNL_AS_LINE_TERMINATOR 0)
set(VERSION ${PACKAGE_VERSION})

if(MSVC) 
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()

include(CheckCSourceCompiles)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckTypeSize)
include(TestBigEndian)

check_function_exists(alloca HAVE_ALLOCA)
check_include_files(alloca.h HAVE_ALLOCA_H)
check_include_files(stdarg.h HAVE_STDARG_PROTOTYPES)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(limits.h HAVE_LIMITS_H)
check_include_files(sys/times.h HAVE_SYS_TIMES_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_type_size(int SIZEOF_INT)
check_type_size(long SIZEOF_LONG)
check_type_size(short SIZEOF_SHORT)
check_include_files("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)

configure_file(config.h.cmake.in "${PROJECT_SOURCE_DIR}/vendor/oniguruma/config.h")

set(HAVE_PROTOTYPES 1)
set(ONIG_SRC
    regerror.c
    regparse.c
    regext.c
    regcomp.c
    regexec.c
    reggnu.c
    regenc.c
    regsyntax.c
    regtrav.c
    regversion.c
    st.c
    regposix.c
    regposerr.c
    onig_init.c
    unicode.c
    ascii.c
    utf8.c
    utf16_be.c
    utf16_le.c
    utf32_be.c
    utf32_le.c
    euc_jp.c
    sjis.c
    iso8859_1.c
    iso8859_2.c
    iso8859_3.c
    iso8859_4.c
    iso8859_5.c
    iso8859_6.c
    iso8859_7.c
    iso8859_8.c
    iso8859_9.c
    iso8859_10.c
    iso8859_11.c
    iso8859_13.c
    iso8859_14.c
    iso8859_15.c
    iso8859_16.c
    euc_tw.c
    euc_kr.c
    big5.c
    gb18030.c
    koi8_r.c
    cp1251.c
    euc_jp_prop.c
    sjis_prop.c
    unicode_unfold_key.c
    unicode_fold1_key.c
    unicode_fold2_key.c
    unicode_fold3_key.c
)

add_library(onig ${ONIG_SRC})
target_compile_options(onig PRIVATE "$<$<CONFIG:DEBUG>:${VENDOR_DEBUG_FLAGS}>")
target_compile_definitions(onig PRIVATE ONIGURUMA_EXPORT)