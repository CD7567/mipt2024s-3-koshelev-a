#include <gtest/gtest.h>

#include "list-stack-tests/list_stack_test_primitive.cxx"
#include "list-stack-tests/list_stack_test_complex.cxx"
#include "array-stack-tests/array_stack_test_primitive.cxx"
#include "array-stack-tests/array_stack_test_complex.cxx"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
