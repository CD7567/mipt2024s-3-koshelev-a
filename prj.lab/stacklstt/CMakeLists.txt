###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACKLSTT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        STACKLSTT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stacklstt
        ${STACKLSTT_HEADERS}
        ${STACKLSTT_SOURCES}
)

target_include_directories(
        stacklstt
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
        stacklstt
        PROPERTIES
        LINKER_LANGUAGE CXX
)

###############################################################################
## dependencies ###############################################################
###############################################################################

target_link_libraries(
        stacklstt
        PUBLIC
        timer
)
