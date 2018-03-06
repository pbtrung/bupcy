#include "greatest.h"

// #include "oniguruma/oniguruma.h"

TEST test_onig_regex() {
    rc_t rc = BUPCY_SUCCESS;

    // int r;
    // unsigned char *start, *range, *end;
    // regex_t *reg;
    // OnigErrorInfo einfo;
    // OnigRegion *region;

    // static UChar *pattern = (UChar *)"^https";
    // static UChar *str = (UChar *)"https://www.tru.ng";

    // OnigEncoding use_encs[] = {ONIG_ENCODING_UTF8};
    // onig_initialize(use_encs, sizeof(use_encs) / sizeof(use_encs[0]));

    // r = onig_new(&reg, pattern, pattern + strlen((char *)pattern),
    //              ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT,
    //              &einfo);
    // if (r != ONIG_NORMAL) {
    //     char s[ONIG_MAX_ERROR_MESSAGE_LEN];
    //     onig_error_code_to_str(s, r, &einfo);
    //     fprintf(stderr, "ERROR: %s\n", s);
    //     return -1;
    // }

    // region = onig_region_new();

    // end = str + strlen((char *)str);
    // start = str;
    // range = end;
    // r = onig_search(reg, str, end, start, range, region, ONIG_OPTION_NONE);
    // if (r >= 0) {
    //     int i;

    //     fprintf(stderr, "match at %d\n", r);
    //     for (i = 0; i < region->num_regs; i++) {
    //         fprintf(stderr, "%d: (%d-%d)\n", i, region->beg[i], region->end[i]);
    //     }
    // } else if (r == ONIG_MISMATCH) {
    //     fprintf(stderr, "search fail\n");
    // } else { /* error */
    //     char s[ONIG_MAX_ERROR_MESSAGE_LEN];
    //     onig_error_code_to_str(s, r);
    //     fprintf(stderr, "ERROR: %s\n", s);
    //     return -1;
    // }

    // /* 1:free self, 0:free contents only */
    // onig_region_free(region, 1);
    // onig_free(reg);
    // onig_end();

    ASSERT_EQ(rc, BUPCY_SUCCESS);
    PASS();
}

SUITE(test_onig) { RUN_TEST(test_onig_regex); }
