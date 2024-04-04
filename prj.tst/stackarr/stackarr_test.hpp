#ifndef STACKARR_TEST_HPP
#define STACKARR_TEST_HPP

#include <doctest/doctest.h>

#include "../common_definitions.hpp"
#include "stackarr.hpp"

TEST_SUITE("TestStackArr") {
    TEST_CASE("TestPushSize") {
        StackArr stack;
        auto data = genData<float>();

        REQUIRE(stack.IsEmpty());

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            stack.Push(data[i]);
            REQUIRE_EQ(stack.Size(), i + 1);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        StackArr stack;
        auto data = genData<float>();

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            stack.Push(data[i]);
            REQUIRE_EQ(stack.Top(), data[i]);
        }
    }

    TEST_CASE("TestPushPop") {
        StackArr stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
            REQUIRE_EQ(stack.Top(), data[i - 1]);
            stack.Pop();
        }

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);
    }

    TEST_CASE("TestShrink") {
        StackArr stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        stack.Shrink();
        REQUIRE_EQ(stack.Size(), stack.Capacity());
        REQUIRE_FALSE(stack.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
            REQUIRE_EQ(stack.Top(), data[i - 1]);
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
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackArr copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copied.Capacity());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(copied.Top(), data[i - 1]);
            copied.Pop();
        }

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(stack.Top(), data[i - 1]);
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
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
            copy_assigned.Push(it);
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copy_assigned.Capacity());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(copy_assigned.Top(), data[i - 1]);
            copy_assigned.Pop();
        }

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(stack.Top(), data[i - 1]);
            stack.Pop();
        }

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackArr stack;
        StackArr moved(std::move(stack));

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);            // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackArr stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackArr moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);            // NOLINT

        REQUIRE_EQ(moved.Size(), TEST_SIZE);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), data[i - 1]);
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

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);            // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackArr stack;
        StackArr move_assigned;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
            move_assigned.Push(it);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrException&);            // NOLINT

        REQUIRE_EQ(move_assigned.Size(), TEST_SIZE);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), data[i - 1]);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrException&);
    }
}

#endif  // STACKARR_TEST_HPP
