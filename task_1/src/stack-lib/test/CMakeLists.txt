###############################################################################
## fetching framework #########################################################
###############################################################################

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

###############################################################################
## test definitions ###########################################################
###############################################################################

file(
    GLOB_RECURSE
    STACK_LIB_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cxx
)

add_executable(
    stack-lib-tests-runner
    ${STACK_LIB_TEST_SOURCES}
)

target_link_libraries(
    stack-lib-tests-runner
    gtest
    gtest_main
    stack-lib
)

gtest_discover_tests(stack-lib-tests-runner)

###############################################################################
## test autorun ###############################################################
###############################################################################

add_custom_target(
    stack-lib-run-tests ALL
    COMMAND stack-lib-tests-runner
)