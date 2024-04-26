###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACKLST_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stacklst
        ${STACKLST_HEADERS}
)

target_include_directories(
        stacklst
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(
        stacklst
        PROPERTIES
        LINKER_LANGUAGE CXX
)

###############################################################################
## dependencies ###############################################################
###############################################################################

target_link_libraries(
        stacklst
        PUBLIC
        stacklstt
)
