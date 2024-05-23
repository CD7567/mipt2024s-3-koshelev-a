###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stacklst
        INTERFACE
)

target_include_directories(
        stacklst
        INTERFACE
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
        INTERFACE
        stacklstt
)
