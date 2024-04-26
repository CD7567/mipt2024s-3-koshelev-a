###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        MOVETESTER_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        movetester
        ${MOVETESTER_HEADERS}
)

target_include_directories(
        movetester
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
        movetester
        PROPERTIES
        LINKER_LANGUAGE CXX
)
