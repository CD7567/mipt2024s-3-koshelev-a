#ifndef STACKLST_TEST_HPP
#define STACKLST_TEST_HPP

#include <doctest/doctest.h>

#include <string>

#include "stacklst/stacklst.hpp"

TEST_SUITE("TestStackLst") {
    TEST_CASE("TestPushSize") {
        StackLst stack;
        auto data = genData<float>();

        REQUIRE(stack.IsEmpty());

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            stack.Push(data[i]);
            REQUIRE_EQ(stack.Size(), i + 1);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        StackLst stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
            REQUIRE_EQ(stack.Top(), it);
        }
    }

    TEST_CASE("TestPushPop") {
        StackLst stack;
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
    }

    TEST_CASE("TestCopyConstructorEmpty") {
        StackLst stack;
        StackLst copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
    }

    TEST_CASE("TestCopyConstructorNotEmpty") {
        StackLst stack;
        auto first_data = genData<float>();
        auto second_data = genData<float>();

        for (auto it : first_data) {
            stack.Push(it);
        }

        StackLst copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            stack.Top() = second_data[i - 1];
            stack.Pop();
        }

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(copied.Top(), first_data[i - 1]);
            copied.Pop();
        }

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
    }

    TEST_CASE("TestCopyAssignmentEmpty") {
        StackLst stack;
        StackLst copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
    }

    TEST_CASE("TestCopyAssignmentNotEmpty") {
        StackLst stack;
        StackLst copy_assigned;
        auto first_data = genData<float>();
        auto second_data = genData<float>();

        for (auto it : first_data) {
            stack.Push(it);
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            stack.Top() = second_data[i - 1];
            stack.Pop();
        }

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(copy_assigned.Top(), first_data[i - 1]);
            copy_assigned.Pop();
        }

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackLst stack;
        StackLst moved(std::move(stack));

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackLst stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackLst moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT

        REQUIRE_EQ(moved.Size(), TEST_SIZE);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), data[i - 1]);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
    }

    TEST_CASE("TestMoveAssignmentEmpty") {
        StackLst stack;
        StackLst move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackLst stack;
        StackLst move_assigned;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT

        REQUIRE_EQ(move_assigned.Size(), TEST_SIZE);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), data[i - 1]);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
    }
}

#endif  // MIPT2024S_3_KOSHELEV_A_STACKLST_TEST_HPP
