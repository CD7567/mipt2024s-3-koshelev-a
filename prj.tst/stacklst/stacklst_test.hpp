#ifndef STACKLST_TEST_HPP
#define STACKLST_TEST_HPP

#include <doctest/doctest.h>

#include "stacklst.hpp"

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

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            stack.Push(data[i]);
            REQUIRE_EQ(stack.Top(), data[i]);
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
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);
    }

    TEST_CASE("TestCopyConstructorEmpty") {
        StackLst stack;
        StackLst copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackLstException&);
    }

    TEST_CASE("TestCopyConstructorNotEmpty") {
        StackLst stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackLst copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());

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
        REQUIRE_THROWS_AS(copied.Pop(), StackLstException&);
    }

    TEST_CASE("TestCopyAssignmentEmpty") {
        StackLst stack;
        StackLst copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstException&);
    }

    TEST_CASE("TestCopyAssignmentNotEmpty") {
        StackLst stack;
        StackLst copy_assigned;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
            copy_assigned.Push(it);
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());

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
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackLst stack;
        StackLst moved(std::move(stack));

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);            // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackLst stack;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackLst moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);            // NOLINT

        REQUIRE_EQ(moved.Size(), TEST_SIZE);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), data[i - 1]);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveAssignmentEmpty") {
        StackLst stack;
        StackLst move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);            // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackLst stack;
        StackLst move_assigned;
        auto data = genData<float>();

        for (auto it : data) {
            stack.Push(it);
            move_assigned.Push(it);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstException&);            // NOLINT

        REQUIRE_EQ(move_assigned.Size(), TEST_SIZE);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), data[i - 1]);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstException&);
    }
}

#endif  // STACKLST_TEST_HPP
