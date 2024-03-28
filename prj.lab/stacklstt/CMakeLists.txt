###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_LSTT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        STACK_LSTT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stack-lstt-lib
        ${STACK_LSTT_HEADERS}
        ${STACK_LSTT_SOURCES}
)

target_include_directories(
        stack-lstt-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stack-lstt-lib PROPERTIES LINKER_LANGUAGE CXX)
