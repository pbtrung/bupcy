file(GLOB BUPCY_TEST_SRC "*.c")
add_executable(test_bupcy "${BUPCY_TEST_SRC}")
target_link_libraries(test_bupcy bupcysrc vendor onig ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(test_bupcy PRIVATE "$<$<CONFIG:DEBUG>:${BUPCY_DEBUG_FLAGS}>")
