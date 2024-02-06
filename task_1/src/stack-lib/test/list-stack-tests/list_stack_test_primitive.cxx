#include "stack-lib/abstract_stack.hxx"
#include <gtest/gtest.h>

#include <stack-lib/list_stack.hxx>

TEST(ListStackTestPrimitive, TestDataManipulation) {
    stack_lib::ListStack<int> stack;

    ASSERT_TRUE(stack.empty());

    for (int i = 1; i < 11; ++i) {
        stack.push(i);

        ASSERT_EQ(stack.top(), i);
        ASSERT_EQ(stack.size(), i);
        ASSERT_FALSE(stack.empty());
    }

    for (int i = 10; i > 0; --i) {
        ASSERT_EQ(stack.top(), i);
        ASSERT_EQ(stack.size(), i);
        ASSERT_FALSE(stack.empty());

        stack.pop(); 
    }

    ASSERT_TRUE(stack.empty());
    ASSERT_THROW(stack.pop(), stack_lib::ExtractFromEmptyStackException);
}

TEST(ListStackTestPrimitive, TestStackCopyConstruction) {
    stack_lib::ListStack<int> stack;
    stack.push(1);

    stack_lib::ListStack<int> copy_constructed_stack(stack);
    
    ASSERT_FALSE(copy_constructed_stack.empty());
    ASSERT_EQ(copy_constructed_stack.top(), 1);

    copy_constructed_stack.top() = 2;
    ASSERT_EQ(stack.top(), 1);
    ASSERT_EQ(copy_constructed_stack.top(), 2);

    copy_constructed_stack.pop();
    ASSERT_TRUE(copy_constructed_stack.empty());
    ASSERT_THROW(copy_constructed_stack.pop(), stack_lib::ExtractFromEmptyStackException);
    ASSERT_FALSE(stack.empty());
    ASSERT_EQ(stack.top(), 1);
}

TEST(ListStackTestPrimitive, TestStackCopyAssignment) {
    stack_lib::ListStack<int> stack;
    stack.push(1);

    stack_lib::ListStack<int> copy_assigned_stack;
    copy_assigned_stack = stack;
    ASSERT_FALSE(copy_assigned_stack.empty());
    ASSERT_EQ(copy_assigned_stack.top(), 1);

    copy_assigned_stack.top() = 2;
    ASSERT_EQ(stack.top(), 1);
    ASSERT_EQ(copy_assigned_stack.top(), 2);

    copy_assigned_stack.pop();
    ASSERT_TRUE(copy_assigned_stack.empty());
    ASSERT_THROW(copy_assigned_stack.pop(), stack_lib::ExtractFromEmptyStackException);
    ASSERT_FALSE(stack.empty());
    ASSERT_EQ(stack.top(), 1);
}

TEST(ListStackTestPrimitive, TestStackMoveConstruction) {
    stack_lib::ListStack<int> stack;
    stack.push(1);

    stack_lib::ListStack<int> move_constructed_stack(std::move(stack));

    ASSERT_FALSE(move_constructed_stack.empty());
    ASSERT_EQ(move_constructed_stack.top(), 1);
}

TEST(ListStackTestPrimitive, TestStackMoveAssignment) {
    stack_lib::ListStack<int> stack;
    stack.push(1);

    stack_lib::ListStack<int> move_assigned_stack;
    move_assigned_stack.push(1);
    move_assigned_stack = std::move(stack);

    ASSERT_FALSE(move_assigned_stack.empty());
    ASSERT_EQ(move_assigned_stack.top(), 1);
}