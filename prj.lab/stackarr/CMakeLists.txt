###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_ARR_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        STACK_ARR_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stack-arr-lib
        ${STACK_ARR_HEADERS}
        ${STACK_ARR_SOURCES}
)

target_include_directories(
        stack-arr-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stack-arr-lib PROPERTIES LINKER_LANGUAGE CXX)
