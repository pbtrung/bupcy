#include "greatest.h"

#include "bstrlib/bstrlib.h"
#include "utils/utils.h"

TEST test_bsplit() {
#if defined(_WIN32)
    bstring str = bfromcstr("C:\\a\\b\\c\\d\\e\\f");
#else
    bstring str = bfromcstr("C:/a/b/c/d/e/f");
#endif
    struct bstrList *blist = bsplit(str, BUPCY_PATH_SEPARATOR);

    ASSERT(biseqStatic(blist->entry[0], "C:") == 1);
    ASSERT(biseqStatic(blist->entry[1], "a") == 1);
    
    bdestroy(str);
    bstrListDestroy(blist);
    PASS();
}

SUITE(test_bstring) { 
    RUN_TEST(test_bsplit); 
}
