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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(
        movetester
        PROPERTIES
        LINKER_LANGUAGE CXX
)

###############################################################################
## dependencies ###############################################################
###############################################################################

target_link_libraries(
        movetester
        PUBLIC
        utils
)
