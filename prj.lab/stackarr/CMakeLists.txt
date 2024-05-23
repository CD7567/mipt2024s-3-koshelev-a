###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        stackarr
        INTERFACE
)

target_include_directories(
        stackarr
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(
        stackarr
        PROPERTIES
        LINKER_LANGUAGE CXX
)

###############################################################################
## dependencies ###############################################################
###############################################################################

target_link_libraries(
        stackarr
        INTERFACE
        stackarrt
)
