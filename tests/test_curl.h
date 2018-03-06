#include "greatest.h"

#include <curl/curl.h>

TEST test_curl_easy() {
    CURL *curl = NULL;
    curl = curl_easy_init();
    ASSERT(curl != NULL);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    PASS();
}

SUITE(test_curl) { 
    RUN_TEST(test_curl_easy); 
}
