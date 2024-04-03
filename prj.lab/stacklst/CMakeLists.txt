###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_LST_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        STACK_LST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stack-lst-lib
        ${STACK_LST_HEADERS}
        ${STACK_LST_SOURCES}
)

target_include_directories(
        stack-lst-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stack-lst-lib PROPERTIES LINKER_LANGUAGE CXX)
