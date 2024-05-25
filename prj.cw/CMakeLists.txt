###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        CW_LIB_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

file(
        GLOB_RECURSE
        CW_LIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.cpp
)

set(
        APP_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(
        cw-lib
        ${CW_LIB_HEADERS}
        ${CW_LIB_SOURCES}
)

target_include_directories(
        cw-lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(
        app
        ${APP_SOURCES}
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
        cw-lib
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        tomlplusplus
)

target_link_libraries(
        app
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        tomlplusplus
        cw-lib
)
