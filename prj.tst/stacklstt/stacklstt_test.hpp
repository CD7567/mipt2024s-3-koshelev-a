#ifndef STACKLSTT_TEST_HPP
#define STACKLSTT_TEST_HPP

#include <doctest/doctest.h>

#include <string>

#include "stacklstt/stacklstt.hpp"
#include "test_struct.hpp"

TEST_SUITE("TestStackLstT") {
    TEST_CASE_TEMPLATE("TestPushSize", T, float, TestStruct) {
        StackLstT<T> stack;
        auto data = genData<T>();

        REQUIRE(stack.IsEmpty());

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            stack.Push(data[i]);
            REQUIRE_EQ(stack.Size(), i + 1);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE_TEMPLATE("TestPushTop", T, float, TestStruct) {
        StackLstT<T> stack;
        auto data = genData<T>();

        for (auto it : data) {
            stack.Push(it);
            REQUIRE_EQ(stack.Top(), it);
        }
    }

    TEST_CASE_TEMPLATE("TestPushPop", T, float, TestStruct) {
        StackLstT<T> stack;
        auto data = genData<T>();

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
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyConstructorEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        StackLstT<T> copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyConstructorNotEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        auto first_data = genData<T>();
        auto second_data = genData<T>();

        for (auto it : first_data) {
            stack.Push(it);
        }

        StackLstT<T> copied(stack);

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
        REQUIRE_THROWS_AS(copied.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyAssignmentEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        StackLstT<T> copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyAssignmentNotEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        StackLstT<T> copy_assigned;
        auto first_data = genData<T>();
        auto second_data = genData<T>();

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
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveConstructorEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        StackLstT<T> moved(std::move(stack));

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);           // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveConstructorNotEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        auto data = genData<T>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackLstT<T> moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);           // NOLINT

        REQUIRE_EQ(moved.Size(), TEST_SIZE);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), data[i - 1]);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveAssignmentEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        StackLstT<T> move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);           // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveAssignmentNotEmpty", T, float, TestStruct) {
        StackLstT<T> stack;
        StackLstT<T> move_assigned;
        auto data = genData<T>();

        for (auto it : data) {
            stack.Push(it);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackLstTException&);           // NOLINT

        REQUIRE_EQ(move_assigned.Size(), TEST_SIZE);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), data[i - 1]);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstTException&);
    }
}

#endif  // STACKLSTT_TEST_HPP
