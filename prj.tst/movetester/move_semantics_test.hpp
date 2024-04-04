#ifndef MIPT2024S_3_KOSHELEV_A_MOVETESTER_TEST_HPP
#define MIPT2024S_3_KOSHELEV_A_MOVETESTER_TEST_HPP

#include <doctest/doctest.h>

#include <chrono>

#include "movetester.hpp"
#include "stackarr.hpp"
#include "stackarrt.hpp"
#include "stacklst.hpp"
#include "stacklstt.hpp"
#include "type_pair.hpp"
#include "utils.hpp"

#define MOVE_TEST_ITERATIONS 10000

template <typename T>
T getObjectForMoveTest();

template <>
MoveTester<true> getObjectForMoveTest() {
    return MoveTester<true>();
}

template <>
MoveTester<false> getObjectForMoveTest() {
    return MoveTester<false>();
}

template <>
StackArr getObjectForMoveTest() {
    auto data = genData<float>();
    StackArr stack;

    for (auto it : data) {
        stack.Push(it);
    }

    return stack;
}

template <>
StackLst getObjectForMoveTest() {
    auto data = genData<float>();
    StackLst stack;

    for (auto it : data) {
        stack.Push(it);
    }

    return stack;
}

template <>
StackArrT<TestStruct> getObjectForMoveTest() {
    auto data = genData<TestStruct>();
    StackArrT<TestStruct> stack;

    for (auto it : data) {
        stack.Push(it);
    }

    return stack;
}

template <>
StackLstT<TestStruct> getObjectForMoveTest() {
    auto data = genData<TestStruct>();
    StackLstT<TestStruct> stack;

    for (auto it : data) {
        stack.Push(it);
    }

    return stack;
}

TEST_SUITE("TestMoveSemantics") {
    TEST_CASE_TEMPLATE(
        "TestCorrectness", T,
        TypePair<MoveTester<true>, std::chrono::nanoseconds>,
        TypePair<MoveTester<false>, std::chrono::nanoseconds>,
        TypePair<StackArr, std::chrono::nanoseconds>,
        TypePair<StackLst, std::chrono::nanoseconds>,
        TypePair<StackArrT<TestStruct>, std::chrono::nanoseconds>,
        TypePair<StackLstT<TestStruct>, std::chrono::nanoseconds>
    ) {
        using ObjectT = typename T::F;
        using ChronoT = typename T::S;

        std::array<size_t, MOVE_TEST_ITERATIONS> copy_construction_time;
        std::array<size_t, MOVE_TEST_ITERATIONS> copy_assignment_time;
        std::array<size_t, MOVE_TEST_ITERATIONS> move_construction_time;
        std::array<size_t, MOVE_TEST_ITERATIONS> move_assignment_time;

        // Measure copy construction time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            copy_construction_time[i] = timeit<ChronoT>(
                [&origin] { ObjectT copy_constructed(origin); });
        }

        // Measure move construction time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            move_construction_time[i] = timeit<ChronoT>(
                [&origin] { ObjectT move_constructed(std::move(origin)); });
        }

        // Measure copy assignment time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            copy_assignment_time[i] = timeit<ChronoT>([&origin] {
                ObjectT copy_assigned;
                copy_assigned = origin;
            });
        }

        // Measure move construction time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            move_assignment_time[i] = timeit<ChronoT>([&origin] {
                ObjectT move_assigned;
                move_assigned = std::move(origin);
            });
        }

        auto copy_construction_deviation = calculate_deviation(copy_construction_time);
        auto copy_assignment_deviation = calculate_deviation(copy_assignment_time);
        auto move_construction_deviation = calculate_deviation(move_construction_time);
        auto move_assignment_deviation = calculate_deviation(move_assignment_time);

        REQUIRE_GE(copy_construction_deviation.first - move_construction_deviation.first,
                   (copy_construction_deviation.second + move_construction_deviation.second) / (double) MOVE_TEST_ITERATIONS);
        REQUIRE_GE(copy_assignment_deviation.first - move_assignment_deviation.first,
                   (copy_assignment_deviation.second + move_assignment_deviation.second) / (double) MOVE_TEST_ITERATIONS);
    }

    TEST_CASE_TEMPLATE(
        "TestIncorrectness", T,
        TypePair<MoveTester<false>, std::chrono::nanoseconds>
    ) {
        using ObjectT = typename T::F;
        using ChronoT = typename T::S;

        std::array<size_t, MOVE_TEST_ITERATIONS> copy_construction_time;
        std::array<size_t, MOVE_TEST_ITERATIONS> copy_assignment_time;
        std::array<size_t, MOVE_TEST_ITERATIONS> move_construction_time;
        std::array<size_t, MOVE_TEST_ITERATIONS> move_assignment_time;

        // Measure copy construction time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            copy_construction_time[i] = timeit<ChronoT>(
                [&origin] { ObjectT copy_constructed(origin); });
        }

        // Measure move construction time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            move_construction_time[i] = timeit<ChronoT>(
                [&origin] { ObjectT move_constructed(std::move(origin)); });
        }

        // Measure copy assignment time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            copy_assignment_time[i] = timeit<ChronoT>([&origin] {
                ObjectT copy_assigned;
                copy_assigned = origin;
            });
        }

        // Measure move construction time
        for (size_t i = 0; i < MOVE_TEST_ITERATIONS; ++i) {
            ObjectT origin = getObjectForMoveTest<ObjectT>();
            move_assignment_time[i] = timeit<ChronoT>([&origin] {
                ObjectT move_assigned;
                move_assigned = std::move(origin);
            });
        }

        auto copy_construction_deviation = calculate_deviation(copy_construction_time);
        auto copy_assignment_deviation = calculate_deviation(copy_assignment_time);
        auto move_construction_deviation = calculate_deviation(move_construction_time);
        auto move_assignment_deviation = calculate_deviation(move_assignment_time);

        REQUIRE_LE(copy_construction_deviation.first - move_construction_deviation.first,
                   (copy_construction_deviation.second + move_construction_deviation.second) / (double) MOVE_TEST_ITERATIONS);
        REQUIRE_LE(copy_assignment_deviation.first - move_assignment_deviation.first,
                   (copy_assignment_deviation.second + move_assignment_deviation.second) / (double) MOVE_TEST_ITERATIONS);
    }
}

#endif  // MIPT2024S_3_KOSHELEV_A_MOVETESTER_TEST_HPP
