cmake_minimum_required(VERSION 3.10)
project(SHAMIR_GIT)

add_compile_options(
    -g
    -O3
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Warray-bounds-pointer-arithmetic
    -Wassign-enum;-Wbad-function-cast
    -Wcast-qual;-Wchar-subscripts
    -Wcomma;-Wconditional-uninitialized
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
    -Wno-deprecated-literal-operator
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_DIR "${PROJECT_DIR}/libs")
set(INCLUDE_DIR "${PROJECT_DIR}/include")

add_library(
    shamir_lib
    libs/storage/storage.cpp
    libs/utils/debug.cpp
)

target_include_directories(
    shamir_lib
    PUBLIC
        ${INCLUDE_DIR}
)

add_library(
    SHAMIR::LIB
    ALIAS
    shamir_lib
)

add_executable(
    execute
    main.cpp
)

target_link_libraries(
    execute
    PRIVATE
    SHAMIR::LIB
)
