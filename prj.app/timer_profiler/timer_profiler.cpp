#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "stackarrt.hpp"
#include "stacklstt.hpp"
#include "test_struct.hpp"
#include "utils.hpp"

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10},{2:>50},{3:>10}";

template <typename T, typename Stack>
inline void testStack(std::ofstream& out, std::string tag, const T& elem,
                      const size_t test_max_size) {
    Stack stack;
    Stack tmp;
    size_t time = 0;

    for (size_t i = 0; i < test_max_size; ++i) {
        TIME(stack.Push(elem), std::chrono::nanoseconds, time);
        out << dyn_format(PRINT_FORMAT, tag, test_max_size, "PUSH", time) << "\n";
    }

    // Measure copy construction time
    TIME(Stack _(stack), std::chrono::nanoseconds, time);  // NOLINT
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "COPY_CONSTR", time)
        << "\n";

    // Measure copy assignment time
    TIME(tmp = stack, std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "COPY_ASSIGN", time)
        << "\n";

    // Measure move construction time
    TIME(Stack _(std::move(tmp)), std::chrono::nanoseconds, time);  // NOLINT
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "MOVE_CONSTR", time)
        << "\n";

    TIME(tmp = stack, std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "COPY_ASSIGN", time)
        << "\n";

    // Measure move assignment time
    Stack move_assigned;
    TIME(move_assigned = std::move(tmp), std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "MOVE_ASSIGN", time)
        << "\n";

    TIME(tmp = stack, std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "COPY_ASSIGN", time)
        << "\n";

    // Measure IsEmpty time
    TIME(auto _ = tmp.IsEmpty(), std::chrono::nanoseconds, time);  // NOLINT
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "IS_EMPTY", time)
        << "\n";

    // Measure Size time
    TIME(auto _ = tmp.Size(), std::chrono::nanoseconds, time);  // NOLINT
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "SIZE", time) << "\n";

    // Measure top time
    TIME(auto _ = tmp.Top(), std::chrono::nanoseconds, time);  // NOLINT
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "TOP", time) << "\n";

    // Measure push time
    TIME(tmp.Push(elem), std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "PUSH", time) << "\n";

    TIME(tmp = stack, std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "COPY_ASSIGN", time)
        << "\n";

    // Measure pop time
    TIME(tmp.Pop(), std::chrono::nanoseconds, time);
    out << dyn_format(PRINT_FORMAT, tag, test_max_size, "POP", time) << "\n";
}

/**
 * Main function of runner
 * @param argc Number of command line arguments
 * @param argv[1] Path to file with test string
 * @param argv[2] Path to file for data output
 * @param argv[3] Amount of iterations
 * @param argv[4] Max size of stack
 * @return Program exit code
 */
int main(int argc, char** argv) {
    std::ofstream::sync_with_stdio(false);
    std::ifstream::sync_with_stdio(false);

    if (argc < 5) {
        std::cerr << "Wrong amount of arguments detected!"
                  << "\n";
        return 1;
    }

    std::ifstream test_string_istream(argv[1], std::ios_base::in);
    std::ofstream csv_ostream(argv[2], std::ios_base::app);

    const size_t test_max_iter = std::stoul(argv[3]);
    const size_t test_max_size = std::stoul(argv[4]);
    std::string test_string;

    if (!test_string_istream.good() || !csv_ostream.good()) {
        std::cerr << "Couldn't open files!"
                  << "\n";
        return 1;
    }

    std::getline(test_string_istream, test_string);
    test_string_istream.close();

    csv_ostream << dyn_format(PRINT_FORMAT, "TAG", "SIZE", "METHOD", "DURATION")
                << "\n";

    for (size_t i = 0; i < test_max_iter; ++i) {
        testStack<TestStruct, StackArrT<TestStruct>>(
            csv_ostream, "ARRAY", TestStruct{i, test_string}, test_max_size);
        testStack<TestStruct, StackLstT<TestStruct>>(
            csv_ostream, "LIST", TestStruct{i, test_string}, test_max_size);
    }

    for (auto& entry : Timer::map_) {
        csv_ostream << dyn_format(PRINT_FORMAT, "INTERNAL", test_max_size,
                                  entry.first,
                                  entry.second.sum_time_ / entry.second.count_)
                    << "\n";
    }
    return 0;
}
