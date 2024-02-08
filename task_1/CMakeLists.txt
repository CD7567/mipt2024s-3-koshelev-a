cmake_minimum_required(VERSION 3.5)

project(stack-demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
    set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer -fsanitize=address")
endif()

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
    GLOB_RECURSE
    RUNNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/*.cxx
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(
    runner
    ${RUNNER_SOURCES}
)

###############################################################################
## dependencies ###############################################################
###############################################################################

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stack-lib
)

target_link_libraries(
    runner PRIVATE
    stack-lib
)