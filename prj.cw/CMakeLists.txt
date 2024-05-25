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
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/config.toml
        ${CMAKE_CURRENT_BINARY_DIR}
        COPYONLY
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
