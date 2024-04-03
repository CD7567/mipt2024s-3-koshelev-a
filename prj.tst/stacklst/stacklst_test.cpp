#include <doctest/doctest.h>

#include "stacklst.hpp"

TEST_SUITE("TestStackLst") {
    TEST_CASE("TestPushSize") {
        StackLst stack;

        REQUIRE(stack.IsEmpty());

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            REQUIRE_EQ(stack.Size(), i);
            REQUIRE_FALSE(stack.IsEmpty());
        }
    }

    TEST_CASE("TestPushTop") {
        StackLst stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            REQUIRE_EQ(stack.Top(), (float)i);
        }
    }

    TEST_CASE("TestPushPop") {
        StackLst stack;

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

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
        }

        StackLst copied(stack);

        REQUIRE_EQ(stack.Size(), copied.Size());
        REQUIRE_EQ(stack.IsEmpty(), copied.IsEmpty());

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

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            copy_assigned.Push((float)i);
        }

        copy_assigned = stack;

        REQUIRE_EQ(stack.Size(), copy_assigned.Size());
        REQUIRE_EQ(stack.IsEmpty(), copy_assigned.IsEmpty());

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
        REQUIRE_THROWS_AS(copy_assigned.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveConstructorEmpty") {
        StackLst stack;
        StackLst moved(std::move(stack));

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstException&);  // NOLINT

        REQUIRE(moved.IsEmpty());
        REQUIRE_EQ(moved.Size(), 0);
        REQUIRE_THROWS_AS(moved.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveConstructorNotEmpty") {
        StackLst stack;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
        }

        StackLst moved(std::move(stack));

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstException&);  // NOLINT

        REQUIRE_EQ(moved.Size(), 10);
        REQUIRE_FALSE(moved.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(moved.Top(), (float)i);
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

        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstException&);  // NOLINT

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstException&);
    }

    TEST_CASE("TestMoveAssignmentNotEmpty") {
        StackLst stack;
        StackLst move_assigned;

        for (size_t i = 1; i < 11; ++i) {
            stack.Push((float)i);
            move_assigned.Push((float)i);
        }

        move_assigned = std::move(stack);

        REQUIRE_EQ(stack.Size(), 0);  // NOLINT
        REQUIRE(stack.IsEmpty());     // NOLINT
        REQUIRE_THROWS_AS(stack.Pop(),
                          StackLstException&);  // NOLINT

        REQUIRE_EQ(move_assigned.Size(), 10);
        REQUIRE_FALSE(move_assigned.IsEmpty());

        for (size_t i = 10; i > 0; --i) {
            REQUIRE_EQ(move_assigned.Top(), (float)i);
            move_assigned.Pop();
        }

        REQUIRE(move_assigned.IsEmpty());
        REQUIRE_EQ(move_assigned.Size(), 0);
        REQUIRE_THROWS_AS(move_assigned.Pop(), StackLstException&);
    }
}
