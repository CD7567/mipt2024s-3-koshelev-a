cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(stack-lib LANGUAGES CXX)

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
    GLOB_RECURSE
    STACK_LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
    stack-lib
    ${STACK_LIB_HEADERS}
)

target_include_directories(
    stack-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(stack-lib PROPERTIES LINKER_LANGUAGE CXX)