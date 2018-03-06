file(GLOB BUPCY_UTILS_SRC "utils/*.c")
file(GLOB BUPCY_CRYPTO_SRC "crypto/*.c")
file(GLOB BUPCY_REPO_SRC "repo/*.c")
list(APPEND BUPCY_SRC "${BUPCY_UTILS_SRC}" "${BUPCY_CRYPTO_SRC}" "${BUPCY_REPO_SRC}")

add_library(bupcysrc "${BUPCY_SRC}")
target_link_libraries(bupcysrc vendor)
if (UNIX_WITH_SUPPORT_COMPILERS)
	target_link_libraries(bupcysrc m)
endif()

target_compile_options(bupcysrc PRIVATE "$<$<CONFIG:DEBUG>:${BUPCY_DEBUG_FLAGS}>")
