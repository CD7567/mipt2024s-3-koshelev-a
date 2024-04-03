#include <doctest/doctest.h>

#include <string>

#include "stackarrt.hpp"
#include "test_struct.hpp"

TEST_SUITE("TestStackArrT") {
    TEST_CASE("TestPushSize") {
        StackArrT<TestStruct> stack;

        REQUIRE(stack.IsEmpty());

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        StackArrT<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
        }
    }

    TEST_CASE("TestPushPop") {
        StackArrT<TestStruct> stack;

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
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);
    }

    TEST_CASE("TestShrink") {
        StackArrT<TestStruct> stack;

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
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);
    }

    TEST_CASE("TestCopyConstructorEmpty") {
        StackArrT<TestStruct> stack;
        StackArrT<TestStruct> copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackArrTException&);
    }

    TEST_CASE("TestCopyConstructorNotEmpty") {
        StackArrT<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
        }

        StackArrT<TestStruct> copied(stack);

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
        REQUIRE_THROWS_AS(copied.Pop(), StackArrTException&);
    }

    TEST_CASE("TestCopyAssignmentEmpty") {
        StackArrT<TestStruct> stack;
        StackArrT<TestStruct> copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrTException&);
    }

    TEST_CASE("TestCopyAssignmentNotEmpty") {
        StackArrT<TestStruct> stack;
        StackArrT<TestStruct> copy_assigned;

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
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrTException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackArrT<TestStruct> stack;
        StackArrT<TestStruct> moved(std::move(stack));

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrTException&);  // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrTException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackArrT<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
        }

        StackArrT<TestStruct> moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrTException&);  // NOLINT

        REQUIRE_EQ(moved.Size(), 10);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(moved.Top().number_, i);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrTException&);
    }

    TEST_CASE("TestMoveAssignmentEmpty") {
        StackArrT<TestStruct> stack;
        StackArrT<TestStruct> move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrTException&);  // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrTException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackArrT<TestStruct> stack;
        StackArrT<TestStruct> move_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            move_assigned.Push(TestStruct{i});
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrTException&);  // NOLINT

        REQUIRE_EQ(move_assigned.Size(), 10);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top().number_, i);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrTException&);
    }
}
