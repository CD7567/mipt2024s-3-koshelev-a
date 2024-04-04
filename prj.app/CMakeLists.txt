###############################################################################
## sources definitions ########################################################
###############################################################################

file(
        GLOB_RECURSE
        STACK_PROFILER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/stack-profiler/*.cpp
)

file(
        GLOB_RECURSE
        JSON_READER_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/json-reader/*.hpp
)

file(
        GLOB_RECURSE
        JSON_READER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/json-reader/*.cpp
)

file(
        GLOB_RECURSE
        STRING_PROFILER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/string-profiler/*.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(
        stack-profiler
        ${STACK_PROFILER_SOURCES}
)

add_executable(
        json-reader
        ${JSON_READER_HEADERS}
        ${JSON_READER_SOURCES}
)

add_executable(
        string-profiler
        ${STRING_PROFILER_SOURCES}
)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(
        nlohmann_json 3.10.5 REQUIRED
)

target_link_libraries(
        stack-profiler PRIVATE
        stack-arrt-lib
        stack-lstt-lib
        util-lib
)

target_link_libraries(
        json-reader PRIVATE
        nlohmann_json::nlohmann_json
        json-lib
        util-lib
)

target_link_libraries(
        string-profiler PRIVATE
        util-lib
)
