###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        TIMER_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        TIMER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        timer
        ${TIMER_HEADERS}
        ${TIMER_SOURCES}
)

target_include_directories(
        timer
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(
        timer
        PROPERTIES
        LINKER_LANGUAGE CXX
)
