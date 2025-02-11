###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        JSON_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        JSON_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        json
        ${JSON_HEADERS}
        ${JSON_SOURCES}
)

target_include_directories(
        json
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(
        json
        PROPERTIES
        LINKER_LANGUAGE CXX
)
