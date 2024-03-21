#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include "util-lib/test_struct.hxx"
#include "util-lib/utils.hxx"

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10},{2:>20},{3:>10}";
constexpr const char* PRINT_H_FORMAT = "{0:>15},{1:>10},{2:>20},{3:>10}";

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
    std::stack<T, C> stack;

    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        size_t push_time = timeit<std::chrono::nanoseconds>(
            [&stack](const T& elem) { stack.push(elem); }, elem);

        out << dyn_format(PRINT_FORMAT, tag, i, "PUSH", push_time) << "\n";

        // Measuring copy construction time
        size_t cpy_c_time = timeit<std::chrono::nanoseconds>(
            [&stack]() { const std::stack<T, C> _(stack); });  // NOLINT

        out << dyn_format(PRINT_FORMAT, tag, i, "COPY_CONSTRUCTOR", cpy_c_time)
            << "\n";
    }
}

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
        testSTL<TestStruct, std::vector<TestStruct>>(
            csv_ostream, "ARRAY", TestStruct{i, test_string}, test_max_size);
        testSTL<TestStruct, std::list<TestStruct>>(
            csv_ostream, "LIST", TestStruct{i, test_string}, test_max_size);
    }

    return 0;
}
