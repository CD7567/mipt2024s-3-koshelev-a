###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        TIMER_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        timer-lib
        ${TIMER_LIB_HEADERS}
)

target_include_directories(
        timer-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(timer-lib PROPERTIES LINKER_LANGUAGE CXX)
