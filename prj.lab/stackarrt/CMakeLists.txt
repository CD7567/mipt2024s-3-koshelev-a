###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_ARRT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        STACK_ARRT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stack-arrt-lib
        ${STACK_ARRT_HEADERS}
        ${STACK_ARRT_SOURCES}
)

target_link_libraries(
        stack-arrt-lib PUBLIC
        timer-lib
)

target_include_directories(
        stack-arrt-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stack-arrt-lib PROPERTIES LINKER_LANGUAGE CXX)
