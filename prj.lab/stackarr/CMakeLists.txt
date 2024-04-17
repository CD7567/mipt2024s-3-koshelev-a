###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_ARR_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stack-arr-lib
        ${STACK_ARR_HEADERS}
)

target_link_libraries(
        stack-arr-lib PUBLIC
        stack-arrt-lib
)

target_include_directories(
        stack-arr-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stack-arr-lib PROPERTIES LINKER_LANGUAGE CXX)
