###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_LST_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stack-lst-lib
        ${STACK_LST_HEADERS}
)

target_link_libraries(
        stack-lst-lib PUBLIC
        stack-lstt-lib
)

target_include_directories(
        stack-lst-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stack-lst-lib PROPERTIES LINKER_LANGUAGE CXX)
