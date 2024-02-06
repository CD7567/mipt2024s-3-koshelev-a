#include "stack-lib/abstract_stack.hxx"
#include <gtest/gtest.h>

#include <stack-lib/list_stack.hxx>
#include <string>

TEST(ListStackTestComplex, TestDataManipulation) {
    stack_lib::ListStack<std::string> stack;

    ASSERT_TRUE(stack.empty());

    for (int i = 1; i < 11; ++i) {
        stack.push(std::to_string(i));

        ASSERT_EQ(stack.top(), std::to_string(i));
        ASSERT_EQ(stack.size(), i);
        ASSERT_FALSE(stack.empty());
    }

    for (int i = 10; i > 0; --i) {
        ASSERT_EQ(stack.top(), std::to_string(i));
        ASSERT_EQ(stack.size(), i);
        ASSERT_FALSE(stack.empty());

        stack.pop(); 
    }

    ASSERT_TRUE(stack.empty());
    ASSERT_THROW(stack.pop(), stack_lib::ExtractFromEmptyStackException);
}

TEST(ListStackTestComplex, TestStackCopyConstruction) {
    stack_lib::ListStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ListStack<std::string> copy_constructed_stack(stack);
    
    ASSERT_FALSE(copy_constructed_stack.empty());
    ASSERT_EQ(copy_constructed_stack.top(), "I am string");

    copy_constructed_stack.top() = "I am longer string";
    ASSERT_EQ(stack.top(), "I am string");
    ASSERT_EQ(copy_constructed_stack.top(), "I am longer string");

    copy_constructed_stack.pop();
    ASSERT_TRUE(copy_constructed_stack.empty());
    ASSERT_THROW(copy_constructed_stack.pop(), stack_lib::ExtractFromEmptyStackException);
    ASSERT_FALSE(stack.empty());
    ASSERT_EQ(stack.top(), "I am string");
}

TEST(ListStackTestComplex, TestStackCopyAssignment) {
    stack_lib::ListStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ListStack<std::string> copy_assigned_stack;
    copy_assigned_stack = stack;

    ASSERT_FALSE(copy_assigned_stack.empty());
    ASSERT_EQ(copy_assigned_stack.top(), "I am string");

    copy_assigned_stack.top() = "I am longer string";
    ASSERT_EQ(stack.top(), "I am string");
    ASSERT_EQ(copy_assigned_stack.top(), "I am longer string");

    copy_assigned_stack.pop();
    ASSERT_TRUE(copy_assigned_stack.empty());
    ASSERT_THROW(copy_assigned_stack.pop(), stack_lib::ExtractFromEmptyStackException);
    ASSERT_FALSE(stack.empty());
    ASSERT_EQ(stack.top(), "I am string");
}

TEST(ListStackTestComplex, TestStackMoveConstruction) {
    stack_lib::ListStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ListStack<std::string> move_constructed_stack(std::move(stack));

    ASSERT_FALSE(move_constructed_stack.empty());
    ASSERT_EQ(move_constructed_stack.top(), "I am string");
}

TEST(ListStackTestComplex, TestStackMoveAssignment) {
    stack_lib::ListStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ListStack<std::string> move_assigned_stack;
    move_assigned_stack.push("I am string");
    move_assigned_stack = std::move(stack);

    ASSERT_FALSE(move_assigned_stack.empty());
    ASSERT_EQ(move_assigned_stack.top(), "I am string");
}