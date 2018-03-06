cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(bupcy VERSION 0.1.0 LANGUAGES C)

if (UNIX AND 
	(
		("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") OR 
	    ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") OR
	    ("${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
	)
)
	set(UNIX_WITH_SUPPORT_COMPILERS TRUE)
elseif (WIN32 AND ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC"))
	set(WIN32_WITH_MSVC TRUE)
else()
	message(FATAL_ERROR "Unsupported OS or compiler")
endif()

set(BUPCY_VERSION_MAJOR 0)
set(BUPCY_VERSION_MINOR 1)
set(BUPCY_VERSION_PATCH 0)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/bupcy_cfg.h.in"
    "${PROJECT_SOURCE_DIR}/include/bupcy_cfg.h"
)

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/vendor"
	"${CURL_INCLUDE_DIRS}"
)

string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)

set(CMAKE_C_STANDARD 99)
if (UNIX_WITH_SUPPORT_COMPILERS)
	set(BUPCY_DEBUG_FLAGS -Og -Wall -Wextra -Wpedantic)
	add_definitions("-DCURL_STATICLIB -DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
elseif (WIN32_WITH_MSVC)
	set(BUPCY_DEBUG_FLAGS)
	add_definitions(
		"/DCURL_STATICLIB"
		"/DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}"
		"/D_CRT_SECURE_NO_DEPRECATE=1" 
		"/D_CRT_SECURE_NO_WARNINGS=1"
	)
endif()

add_subdirectory(vendor)
add_subdirectory(src)

add_executable(bupcy src/main.c)
target_link_libraries(bupcy bupcysrc vendor onig ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES})
target_compile_options(bupcy PRIVATE "$<$<CONFIG:DEBUG>:${BUPCY_DEBUG_FLAGS}>")

add_subdirectory(tests)
