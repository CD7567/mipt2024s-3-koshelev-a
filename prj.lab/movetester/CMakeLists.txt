###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        MOVE_TESTER_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        move-tester-lib
        ${MOVE_TESTER_HEADERS}
)

target_include_directories(
        move-tester-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(move-tester-lib PROPERTIES LINKER_LANGUAGE CXX)
