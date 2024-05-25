###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        APP_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

file(
        GLOB_RECURSE
        APP_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(
        app
        ${APP_HEADERS}
        ${APP_SOURCES}
)

target_include_directories(
        app
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(
        OpenCV REQUIRED
)

find_package(
        spdlog REQUIRED
)

find_package(
        tomlplusplus REQUIRED
)

target_link_libraries(
        app
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        tomlplusplus
)
