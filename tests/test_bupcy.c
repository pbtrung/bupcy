#include "utils/common.h"

#include "test_base58.h"
#include "test_onig.h"

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[]) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(test_base58);
    RUN_SUITE(test_onig);

    GREATEST_MAIN_END();
}
