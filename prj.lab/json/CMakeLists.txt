###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        JSON_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
        GLOB_RECURSE
        JSON_LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        json-lib
        ${JSON_LIB_HEADERS}
        ${JSON_LIB_SOURCES}
)

target_include_directories(
        json-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(json-lib PROPERTIES LINKER_LANGUAGE CXX)
