#ifndef STACKLSTT_TEST_HPP
#define STACKLSTT_TEST_HPP

#include <doctest/doctest.h>

#include <string>

#include "stacklstt.hpp"
#include "test_struct.hpp"

TEST_SUITE("TestStackLstT") {
    TEST_CASE("TestPushSize") {
        StackLstT<TestStruct> stack;

        REQUIRE(stack.IsEmpty());

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        StackLstT<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            REQUIRE_EQ(stack.Top().number_, i);
            REQUIRE_EQ(stack.Top().string_, std::string("I am string"));
        }
    }

    TEST_CASE("TestPushPop") {
        StackLstT<TestStruct> stack;

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
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);
    }

    TEST_CASE("TestCopyConstructorEmpty") {
        StackLstT<TestStruct> stack;
        StackLstT<TestStruct> copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackLstTException&);
    }

    TEST_CASE("TestCopyConstructorNotEmpty") {
        StackLstT<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
        }

        StackLstT<TestStruct> copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());

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
        REQUIRE_THROWS_AS(copied.Pop(), StackLstTException&);
    }

    TEST_CASE("TestCopyAssignmentEmpty") {
        StackLstT<TestStruct> stack;
        StackLstT<TestStruct> copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstTException&);
    }

    TEST_CASE("TestCopyAssignmentNotEmpty") {
        StackLstT<TestStruct> stack;
        StackLstT<TestStruct> copy_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            copy_assigned.Push(TestStruct{i});
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());

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
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstTException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackLstT<TestStruct> stack;
        StackLstT<TestStruct> moved(std::move(stack));

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstTException&);  // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstTException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackLstT<TestStruct> stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
        }

        StackLstT<TestStruct> moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstTException&);  // NOLINT

        REQUIRE_EQ(moved.Size(), 10);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(moved.Top().number_, i);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstTException&);
    }

    TEST_CASE("TestMoveAssignmentEmpty") {
        StackLstT<TestStruct> stack;
        StackLstT<TestStruct> move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstTException&);  // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstTException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackLstT<TestStruct> stack;
        StackLstT<TestStruct> move_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push(TestStruct{i});
            move_assigned.Push(TestStruct{i});
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstTException&);  // NOLINT

        REQUIRE_EQ(move_assigned.Size(), 10);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top().number_, i);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstTException&);
    }
}

#endif  // STACKLSTT_TEST_HPP
