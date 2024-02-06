#include "stack-lib/abstract_stack.hxx"
#include <gtest/gtest.h>

#include <stack-lib/array_stack.hxx>
#include <string>

TEST(ArrayStackTestComplex, TestDataManipulation) {
    stack_lib::ArrayStack<std::string> stack;

    ASSERT_TRUE(stack.empty());

    for (int i = 1; i < 11; ++i) {
        stack.push(std::to_string(i));

        ASSERT_EQ(stack.top(), std::to_string(i));
        ASSERT_EQ(stack.size(), i);
        ASSERT_FALSE(stack.empty());
    }

    stack.shrink();
    ASSERT_EQ(stack.size(), 10);
    ASSERT_EQ(stack.capacity(), 10);
    ASSERT_FALSE(stack.empty());

    for (int i = 10; i > 0; --i) {
        ASSERT_EQ(stack.top(), std::to_string(i));
        ASSERT_EQ(stack.size(), i);
        ASSERT_FALSE(stack.empty());

        stack.pop(); 
    }

    ASSERT_TRUE(stack.empty());
    ASSERT_THROW(stack.pop(), stack_lib::ExtractFromEmptyStackException);
}

TEST(ArrayStackTestComplex, TestStackCopyConstruction) {
    stack_lib::ArrayStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ArrayStack<std::string> copy_constructed_stack(stack);
    
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

TEST(ArrayStackTestComplex, TestStackCopyAssignment) {
    stack_lib::ArrayStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ArrayStack<std::string> copy_assigned_stack;
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

TEST(ArrayStackTestComplex, TestStackMoveConstruction) {
    stack_lib::ArrayStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ArrayStack<std::string> move_constructed_stack(std::move(stack));

    ASSERT_FALSE(move_constructed_stack.empty());
    ASSERT_EQ(move_constructed_stack.top(), "I am string");
}

TEST(ArrayStackTestComplex, TestStackMoveAssignment) {
    stack_lib::ArrayStack<std::string> stack;
    stack.push("I am string");

    stack_lib::ArrayStack<std::string> move_assigned_stack;
    move_assigned_stack.push("I am string");
    move_assigned_stack = std::move(stack);

    ASSERT_FALSE(move_assigned_stack.empty());
    ASSERT_EQ(move_assigned_stack.top(), "I am string");
}