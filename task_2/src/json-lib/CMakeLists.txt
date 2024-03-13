cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(json-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        JSON_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx
)

file(
        GLOB_RECURSE
        JSON_LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        json-lib
        ${JSON_LIB_HEADERS}
        ${JSON_LIB_SOURCES}
)

target_include_directories(
        json-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(json-lib PROPERTIES LINKER_LANGUAGE CXX)