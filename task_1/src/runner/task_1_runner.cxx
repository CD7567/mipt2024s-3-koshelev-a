#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "stack-lib/abstract_stack.hxx"
#include "stack-lib/array_stack.hxx"
#include "stack-lib/list_stack.hxx"
#include "util-lib/utils.hxx"

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10},{2:>20},{3:>10}";
constexpr const char* PRINT_H_FORMAT = "{0:>15},{1:>10},{2:>20},{3:>10}";

/**
 * Test custom stack implementations
 * @tparam T Template parameter for stack
 * @tparam Stack Stack implementation
 * @param out Fstream to store data
 * @param tag Discriminator for data processing
 * @param elem Element to store in stack
 * @param test_max_size Max amount of elements for test
 */
template <typename T, typename Stack>
inline void testStack(std::ofstream& out, std::string tag, const T& elem,
                      const size_t test_max_size) {
    static_assert(std::is_base_of_v<stack_lib::AbstractStack<T>, Stack>);

    Stack stack;

    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        size_t push_time = timeit<std::chrono::nanoseconds>(
            [&stack](const T& elem) { stack.Push(elem); }, elem);

        out << dyn_format(PRINT_FORMAT, tag, i, "PUSH", push_time) << "\n";

        // Measuring copy construction time
        size_t cpy_c_time = timeit<std::chrono::nanoseconds>(
            [&stack]() { const Stack _(stack); });

        out << dyn_format(PRINT_FORMAT, tag, i, "COPY_CONSTRUCTOR", cpy_c_time)
            << "\n";
    }
}

/**
 * Test custom stack implementations with virtual calls
 * @tparam T Template parameter for stack
 * @tparam Stack Stack implementation
 * @param out Fstream to store data
 * @param tag Discriminator for data processing
 * @param elem Element to store in stack
 * @param test_max_size Max amount of elements for test
 */
template <typename T, typename Stack>
inline void testStackVirtual(std::ofstream& out, std::string tag, const T& elem,
                             const size_t test_max_size) {
    static_assert(std::is_base_of_v<stack_lib::AbstractStack<T>, Stack>);

    Stack raw_stack;
    auto& stack = dynamic_cast<stack_lib::AbstractStack<T>&>(raw_stack);

    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        size_t push_time = timeit<std::chrono::nanoseconds>(
            [&stack](const T& elem) { stack.Push(elem); }, elem);

        out << dyn_format(PRINT_FORMAT, tag, i, "PUSH", push_time) << "\n";
    }
}

/**
 * Main function of runner
 * @param argc Number of command line arguments
 * @param argv[1] Path to file with test string
 * @param argv[2] Path to file for data output
 * @param argv[3] Boolean whether to print header
 * @param argv[4] Amount of iterations
 * @param argv[5] Max size of stack
 * @return Program exit code
 */
int main(int argc, char** argv) {
    std::ofstream::sync_with_stdio(false);
    std::ifstream::sync_with_stdio(false);

    if (argc < 6) {
        std::cerr << "Wrong amount of arguments detected!"
                  << "\n";
        return 1;
    }

    std::ifstream test_string_istream(argv[1], std::ios_base::in);
    std::ofstream csv_ostream(argv[2], std::ios_base::app);
    std::string test_string;

    const size_t test_max_iter = std::stoul(argv[4]);
    const size_t test_max_size = std::stoul(argv[5]);

    if (!test_string_istream.good() || !csv_ostream.good()) {
        std::cerr << "Couldn't open files!"
                  << "\n";
        return 1;
    }

    std::getline(test_string_istream, test_string);
    test_string_istream.close();

    if (std::strcmp(argv[3], "true") == 0) {
        csv_ostream << dyn_format(PRINT_H_FORMAT, "TAG", "SIZE", "METHOD",
                                  "DURATION")
                    << "\n";
    }

    for (size_t i = 0; i < test_max_iter; ++i) {
        testStack<TestStruct, stack_lib::ArrayStack<TestStruct>>(
            csv_ostream, "ARRAY", TestStruct{i, test_string}, test_max_size);
        testStack<TestStruct, stack_lib::ListStack<TestStruct>>(
            csv_ostream, "LIST", TestStruct{i, test_string}, test_max_size);
        testStackVirtual<TestStruct, stack_lib::ArrayStack<TestStruct>>(
            csv_ostream, "VIRT_ARRAY", TestStruct{i, test_string},
            test_max_size);
        testStackVirtual<TestStruct, stack_lib::ListStack<TestStruct>>(
            csv_ostream, "VIRT_LIST", TestStruct{i, test_string},
            test_max_size);
    }

    return 0;
}
