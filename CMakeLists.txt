cmake_minimum_required(VERSION 3.10)
project(SHAMIR_GIT)
include(FetchContent)

message(STATUS "Using the CLI11 library")
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG "main"
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(
    CLI11
)

get_target_property(
    CLI11_INCLUDE_DIR
    CLI11::CLI11
    INTERFACE_INCLUDE_DIRECTORIES
)

if(NOT TARGET CLI11)
    message(
        FATAL_ERROR
        "Could not find CLI11 library"
    )
endif()

add_compile_options(
    -g
    -O3
    -Wall
    -Wextra
    -Wpedantic
    -Warray-bounds-pointer-arithmetic
    -Wassign-enum
    -Wbad-function-cast
    -Wcast-qual
    -Wchar-subscripts
    -Wcomma
    -Wconditional-uninitialized
    -Wconversion
    -Wdelete-non-virtual-dtor
    -Wdeprecated
    -Wduplicate-enum
    -Wduplicate-method-arg
    -Wembedded-directive
    -Wfor-loop-analysis
    -Wformat-pedantic
    -Widiomatic-parentheses
    -Wimplicit-fallthrough
    -Wpedantic
    -Wrange-loop-analysis
    -Wredundant-parens
    -Wreserved-id-macro
    -Wshadow
    -Wundefined-reinterpret-cast
    -Wunreachable-code-aggressive
    -Wno-missing-braces
    -Wno-deprecated-copy-dtor)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_DIR "${PROJECT_DIR}/libs")
set(INCLUDE_DIR "${PROJECT_DIR}/include")

add_library(
    shamir_lib
        libs/math/math.cpp
        libs/utils/debug.cpp
)

target_include_directories(
    shamir_lib
    PUBLIC
        ${INCLUDE_DIR}
)

add_library(
    server_lib
        libs/server/client.cpp
        libs/server/tcp_server.cpp
        libs/threadpool/thread_pool.cpp
        libs/storage/storage.cpp
        libs/math/math.cpp
        libs/utils/debug.cpp
)

target_include_directories(
    server_lib
    PUBLIC
        ${INCLUDE_DIR}
        ${CLI11_INCLUDE_DIR}
)

target_link_libraries(
    server_lib
    PUBLIC
        -lboost_system
        CLI11::CLI11
)

add_library(
    SERVER::LIB
    ALIAS
        server_lib
)

add_library(
    SHAMIR::LIB
    ALIAS
        shamir_lib
)

add_executable(
    unittest
        test/math_test.cpp
)

add_executable(
    client
        execute/client_driver.cpp
)

add_executable(
    server
        execute/server_driver.cpp
)

target_link_libraries(
    server
    PRIVATE
        SHAMIR::LIB
        SERVER::LIB
)

target_link_libraries(
    client
    PRIVATE
        SHAMIR::LIB
        SERVER::LIB
)

target_link_libraries(
    unittest
    PRIVATE
       SHAMIR::LIB
)