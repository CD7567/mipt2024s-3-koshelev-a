#ifndef STACKARR_TEST_HPP
#define STACKARR_TEST_HPP

#include <doctest/doctest.h>

#include "stackarr.hpp"

TEST_SUITE("TestStackArr") {
    TEST_CASE("TestPushSize") {
        StackArr stack;

        REQUIRE(stack.IsEmpty());

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        StackArr stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            REQUIRE_EQ(stack.Top(), (float)i);
        }
    }

    TEST_CASE("TestPushPop") {
        StackArr stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            REQUIRE_EQ(stack.Top(), (float)i);
        }

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
            REQUIRE_EQ(stack.Top(), (float)i);
            stack.Pop();
        }

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);
    }

    TEST_CASE("TestShrink") {
        StackArr stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            REQUIRE_EQ(stack.Top(), i);
        }

        stack.Shrink();
        REQUIRE_EQ(stack.Size(), stack.Capacity());
        REQUIRE_FALSE(stack.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
            REQUIRE_EQ(stack.Top(), (float)i);
            stack.Pop();
        }

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);
    }

    TEST_CASE("TestCopyConstructorEmpty") {
        StackArr stack;
        StackArr copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackArrException&);
    }

    TEST_CASE("TestCopyConstructorNotEmpty") {
        StackArr stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
        }

        StackArr copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copied.Capacity());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(copied.Top(), (float)i);
            copied.Pop();
        }

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Top(), (float)i);
            stack.Pop();
        }

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackArrException&);
    }

    TEST_CASE("TestCopyAssignmentEmpty") {
        StackArr stack;
        StackArr copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrException&);
    }

    TEST_CASE("TestCopyAssignmentNotEmpty") {
        StackArr stack;
        StackArr copy_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            copy_assigned.Push((float)i);
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copy_assigned.Capacity());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(copy_assigned.Top(), (float)i);
            copy_assigned.Pop();
        }

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(stack.Top(), (float)i);
            stack.Pop();
        }

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackArr stack;
        StackArr moved(std::move(stack));

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrException&);  // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackArr stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
        }

        StackArr moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrException&);  // NOLINT

        REQUIRE_EQ(moved.Size(), 10);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), (float)i);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveAssignmentEmpty") {
        StackArr stack;
        StackArr move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrException&);  // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackArr stack;
        StackArr move_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            move_assigned.Push((float)i);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackArrException&);  // NOLINT

        REQUIRE_EQ(move_assigned.Size(), 10);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), (float)i);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrException&);
    }
}

#endif  // STACKARR_TEST_HPP
