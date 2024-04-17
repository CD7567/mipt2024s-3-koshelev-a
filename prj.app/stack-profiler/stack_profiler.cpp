#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include "stackarrt.hpp"
#include "stacklstt.hpp"
#include "test_struct.hpp"
#include "utils.hpp"

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10},{2:>20},{3:>10}";

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
    Stack stack;

    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        size_t push_time;
        TIME(stack.Push(elem), std::chrono::nanoseconds, push_time);

        out << dyn_format(PRINT_FORMAT, tag, i, "PUSH", push_time) << "\n";

        // Measuring copy construction time
        size_t cpy_c_time;
        TIME(Stack _(stack), std::chrono::nanoseconds, cpy_c_time);

        out << dyn_format(PRINT_FORMAT, tag, i, "COPY_CONSTRUCTOR", cpy_c_time)
            << "\n";
    }
}

/**
 * Test STL stack implementations
 * @tparam T Template parameter for stack
 * @tparam C Base STL container for std::stack
 * @param out Fstream to store data
 * @param tag Discriminator for data processing
 * @param elem Element to store in stack
 * @param test_max_size Max amount of elements for test
 */
template <typename T, typename C>
inline void testSTL(std::ofstream& out, std::string tag, const T& elem,
                    const size_t test_max_size) {
    typedef std::stack<T, C> STLStack;
    STLStack stack;

    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        size_t push_time;
        TIME(stack.push(elem), std::chrono::nanoseconds, push_time);

        out << dyn_format(PRINT_FORMAT, tag, i, "PUSH", push_time) << "\n";

        // Measuring copy construction time
        size_t cpy_c_time;
        TIME(STLStack _(stack), std::chrono::nanoseconds, cpy_c_time);

        out << dyn_format(PRINT_FORMAT, tag, i, "COPY_CONSTRUCTOR", cpy_c_time)
            << "\n";
    }
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
        testSTL<TestStruct, std::vector<TestStruct>>(
            csv_ostream, "STL_ARRAY", TestStruct{i, test_string}, test_max_size);
        testSTL<TestStruct, std::list<TestStruct>>(
            csv_ostream, "STL_LIST", TestStruct{i, test_string}, test_max_size);
    }

    return 0;
}
