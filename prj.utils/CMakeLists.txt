###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        UTILS_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        utils
        ${UTILS_HEADERS}
)

target_include_directories(
        utils
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(
        utils
        PROPERTIES
        LINKER_LANGUAGE CXX
)
