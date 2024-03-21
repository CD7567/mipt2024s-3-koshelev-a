cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(mipt2024s-3-koshelev-a)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
## profiles settings ##########################################################
###############################################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
    set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer -fsanitize=address")

    set(DO_COMPILE_TESTS ON)
    set(DO_AUTORUN_TESTS ON)
endif()

###############################################################################
## dependencies ###############################################################
###############################################################################

if(DO_COMPILE_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/task_1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/task_2)