###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACKARRT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        STACKARRT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stackarrt
        ${STACKARRT_HEADERS}
        ${STACKARRT_SOURCES}
)

target_include_directories(
        stackarrt
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
        stackarrt
        PROPERTIES
        LINKER_LANGUAGE CXX
)

###############################################################################
## dependencies ###############################################################
###############################################################################

target_link_libraries(
        stackarrt
        PUBLIC
        timer
)
