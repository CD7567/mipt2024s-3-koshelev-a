#include <doctest/doctest.h>

#include <string>

#include "stack-lib/array_stack.hxx"
#include "util-lib/utils.hxx"

TEST_SUITE("TestArrayStack") {
    TEST_CASE("TestPushSize") {
        stack_lib::ArrayStack<TestStruct> stack;

        REQUIRE(stack.IsEmpty());

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        stack_lib::ArrayStack<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
        }
    }

    TEST_CASE("TestPushPop") {
        stack_lib::ArrayStack<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
        }

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
            REQUIRE_EQ(stack.Top().number_, i);
            stack.Pop();
        }

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestShrink") {
        stack_lib::ArrayStack<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
        }

        stack.Shrink();
        REQUIRE_EQ(stack.Size(), stack.Capacity());
        REQUIRE_FALSE(stack.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
            stack.Pop();
        }

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestCopyConstructorEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;
        stack_lib::ArrayStack<TestStruct> copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestCopyConstructorNotEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
        }

        stack_lib::ArrayStack<TestStruct> copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copied.Capacity());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(copied.Top().number_, i);
            copied.Top().string_ = "I am modified string";
            copied.Pop();
        }

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
            stack.Pop();
        }

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestCopyAssignmentEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;
        stack_lib::ArrayStack<TestStruct> copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestCopyAssignmentNotEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;
        stack_lib::ArrayStack<TestStruct> copy_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            copy_assigned.Push(TestStruct{i});
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copy_assigned.Capacity());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(copy_assigned.Top().number_, i);
            copy_assigned.Top().string_ = "I am modified string";
            copy_assigned.Pop();
        }

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
            stack.Pop();
        }

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;
        stack_lib::ArrayStack<TestStruct> moved(std::move(stack));

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(
            stack.Pop(),
            stack_lib::ExtractFromEmptyStackException&);  // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
        }

        stack_lib::ArrayStack<TestStruct> moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(
            stack.Pop(),
            stack_lib::ExtractFromEmptyStackException&);  // NOLINT

        REQUIRE_EQ(moved.Size(), 10);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(moved.Top().number_, i);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestMoveAssignmentEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;
        stack_lib::ArrayStack<TestStruct> move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(
            stack.Pop(),
            stack_lib::ExtractFromEmptyStackException&);  // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        stack_lib::ArrayStack<TestStruct> stack;
        stack_lib::ArrayStack<TestStruct> move_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            move_assigned.Push(TestStruct{i});
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(
            stack.Pop(),
            stack_lib::ExtractFromEmptyStackException&);  // NOLINT

        REQUIRE_EQ(move_assigned.Size(), 10);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top().number_, i);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(),
                          stack_lib::ExtractFromEmptyStackException&);
    }
}