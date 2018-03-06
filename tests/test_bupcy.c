#include "utils/common.h"

#include "test_base58.h"
#include "test_onig.h"
#include "test_bstring.h"
#include "test_curl.h"

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[]) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(test_base58);
    RUN_SUITE(test_onig);
    RUN_SUITE(test_bstring);
    RUN_SUITE(test_curl);

    GREATEST_MAIN_END();
}
