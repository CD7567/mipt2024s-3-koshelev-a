###############################################################################
## target definitions #########################################################
###############################################################################

file(
    GLOB_RECURSE
    TEST_RUNNER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hxx
)

file(
    GLOB_RECURSE
    TEST_RUNNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)

file(
    COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(
    test-runner
    ${TEST_RUNNER_HEADERS}
    ${TEST_RUNNER_SOURCES}
)

###############################################################################
## dependencies ###############################################################
###############################################################################

find_package(doctest REQUIRED)

target_link_libraries(
    test-runner PRIVATE
    doctest::doctest
    stack-lib
    json-lib
    util-lib
)

###############################################################################
## test autorun ###############################################################
###############################################################################

if(DO_AUTORUN_TESTS)
    add_custom_target(
        run-tests ALL
        COMMAND test-runner
    )
endif()