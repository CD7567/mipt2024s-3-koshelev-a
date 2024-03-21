cmake_minimum_required(VERSION 3.5)

###############################################################################
## project definition #########################################################
###############################################################################

project(task_2)

if(DO_JSON_SKIP_WRITING)
    add_definitions(-DDO_JSON_SKIP_WRITING)
endif()

###############################################################################
## sources definitions ########################################################
###############################################################################

file(
    GLOB_RECURSE
    TASK_2_RUNNER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/*.hxx
)

file(
    GLOB_RECURSE
    TASK_2_RUNNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/*.cxx
)

file(
    GLOB_RECURSE
    TASK_2_LIB_RUNNER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib-runner/*.hxx
)

file(
    GLOB_RECURSE
    TASK_2_LIB_RUNNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib-runner/*.cxx
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(
    task-2-runner
    ${TASK_2_RUNNER_HEADERS}
    ${TASK_2_RUNNER_SOURCES}
)

add_executable(
    task-2-lib-runner
    ${TASK_2_LIB_RUNNER_HEADERS}
    ${TASK_2_LIB_RUNNER_SOURCES}
)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(
    nlohmann_json 3.10.5 REQUIRED
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/json-lib
)

target_link_libraries(
    task-2-runner PRIVATE
    json-lib
    util-lib
)

target_link_libraries(
    task-2-lib-runner PRIVATE
    nlohmann_json::nlohmann_json
    util-lib
)
