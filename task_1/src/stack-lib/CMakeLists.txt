cmake_minimum_required(VERSION 3.5)

project(stack-lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set(CLANG_TIDY_EXCLUDE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/build/*")

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
    GLOB_RECURSE
    STACK_LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx
)

file(
    GLOB_RECURSE
    STACK_LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
    stack-lib
    ${STACK_LIB_HEADERS}
    ${STACK_LIB_SOURCES}
)

target_include_directories(
    stack-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(stack-lib PROPERTIES LINKER_LANGUAGE CXX)

###############################################################################
## testing ####################################################################
###############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=.*;")
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()
