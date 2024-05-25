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
        MAIN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

set(
        GEN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gen.cpp
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
        main
        ${MAIN_SOURCES}
)

add_executable(
        gen
        ${GEN_SOURCES}
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
        main
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        cw-lib
)

target_link_libraries(
        gen
        PUBLIC
        ${OpenCV_LIBS}
        spdlog::spdlog
        cw-lib
)
