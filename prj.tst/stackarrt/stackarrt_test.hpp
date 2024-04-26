#ifndef STACKARRT_TEST_HPP
#define STACKARRT_TEST_HPP

#include <doctest/doctest.h>

#include <string>

#include "stackarrt/stackarrt.hpp"
#include "test_struct.hpp"

TEST_SUITE("TestStackArrT") {
    TEST_CASE_TEMPLATE("TestPushSize", T, float, TestStruct) {
        StackArrT<T> stack;
        auto data = genData<T>();

        REQUIRE(stack.IsEmpty());

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            stack.Push(data[i]);
            REQUIRE_EQ(stack.Size(), i + 1);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE_TEMPLATE("TestPushTop", T, float, TestStruct) {
        StackArrT<T> stack;
        auto data = genData<T>();

        for (auto it : data) {
            stack.Push(it);
            REQUIRE_EQ(stack.Top(), it);
        }
    }

    TEST_CASE_TEMPLATE("TestPushPop", T, float, TestStruct) {
        StackArrT<T> stack;
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
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestShrink", T, float, TestStruct) {
        StackArrT<T> stack;
        auto data = genData<T>();

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
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyConstructorEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        StackArrT<T> copied(stack);

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);

        REQUIRE(copied.IsEmpty());
        REQUIRE_EQ(copied.Size(), 0);
        REQUIRE_THROWS_AS(copied.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyConstructorNotEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        auto first_data = genData<T>();
        auto second_data = genData<T>();

        for (auto it : first_data) {
            stack.Push(it);
        }

        StackArrT<T> copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copied.Capacity());

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
        REQUIRE_THROWS_AS(copied.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyAssignmentEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        StackArrT<T> copy_assigned;

        copy_assigned = stack;

        REQUIRE(stack.IsEmpty());
        REQUIRE_EQ(stack.Size(), 0);
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);

        REQUIRE(copy_assigned.IsEmpty());
        REQUIRE_EQ(copy_assigned.Size(), 0);
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestCopyAssignmentNotEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        StackArrT<T> copy_assigned;
        auto first_data = genData<T>();
        auto second_data = genData<T>();

        for (auto it : first_data) {
            stack.Push(it);
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());
        REQUIRE_EQ(stack.Capacity(), copy_assigned.Capacity());

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
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveConstructorEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        StackArrT<T> moved(std::move(stack));

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);           // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveConstructorNotEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        auto data = genData<T>();

        for (auto it : data) {
            stack.Push(it);
        }

        StackArrT<T> moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);           // NOLINT

        REQUIRE_EQ(moved.Size(), TEST_SIZE);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), data[i - 1]);
            moved.Pop();
        }

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveAssignmentEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        StackArrT<T> move_assigned;

        move_assigned = std::move(stack);

        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);           // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrTException&);
    }

    TEST_CASE_TEMPLATE("TestMoveAssignmentNotEmpty", T, float, TestStruct) {
        StackArrT<T> stack;
        StackArrT<T> move_assigned;
        auto data = genData<T>();

        for (auto it : data) {
            stack.Push(it);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);                                   // NOLINT
        REQUIRE(stack.IsEmpty());                                      // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(), StackArrTException&);           // NOLINT

        REQUIRE_EQ(move_assigned.Size(), TEST_SIZE);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = TEST_SIZE; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), data[i - 1]);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackArrTException&);
    }
}

#endif  // STACKARRT_TEST_HPP
