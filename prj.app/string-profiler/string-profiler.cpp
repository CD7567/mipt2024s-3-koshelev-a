#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "utils.hpp"

constexpr const char* PRINT_FORMAT = "{0:>10},{1:>10},{2:>20},{3:>10}";

/**
 * Test std::string
 * @param out Fstream to store data
 * @param test_max_size Max string length for test
 */
void testString(std::ofstream& out, const size_t test_max_size) {
    std::string str;

    for (size_t i = 0; i < test_max_size; ++i) {
        size_t copy_construction_time;
        TIME(std::string copy_constructed(str), std::chrono::nanoseconds, copy_construction_time);

        out << dyn_format(PRINT_FORMAT, "COPY", i, "CONSTRUCTION",
                          copy_construction_time)
            << "\n";

        size_t copy_assignment_time;
        TIME(std::string copy_assigned; copy_assigned = str, std::chrono::nanoseconds, copy_assignment_time);

        out << dyn_format(PRINT_FORMAT, "COPY", i, "ASSIGNMENT",
                          copy_assignment_time)
            << "\n";

        std::string tmp = str;

        size_t move_construction_time;
        TIME(std::string move_constructed(std::move(tmp)), std::chrono::nanoseconds, move_construction_time);

        out << dyn_format(PRINT_FORMAT, "MOVE", i, "CONSTRUCTION",
                          move_construction_time)
            << "\n";

        tmp = str;

        size_t move_assignment_time;
        TIME(std::string move_assigned; move_assigned = std::move(tmp), std::chrono::nanoseconds, move_assignment_time);

        out << dyn_format(PRINT_FORMAT, "MOVE", i, "ASSIGNMENT",
                          move_assignment_time)
            << "\n";

        str += genRandomChar();
    }
}

/**
 * Main function of runner
 * @param argc Number of command line arguments
 * @param argv[1] Path to file for data output
 * @param argv[2] Amount of iterations
 * @param argv[3] Max size of stack
 * @return Program exit code
 */
int main(int argc, char** argv) {
    std::ofstream::sync_with_stdio(false);
    std::ifstream::sync_with_stdio(false);

    if (argc < 4) {
        std::cerr << "Wrong amount of arguments detected!"
                  << "\n";
        return 1;
    }

    std::ofstream csv_ostream(argv[1], std::ios_base::app);
    const size_t test_max_iter = std::stoul(argv[2]);
    const size_t test_max_size = std::stoul(argv[3]);

    if (!csv_ostream.good()) {
        std::cerr << "Couldn't open files!"
                  << "\n";
        return 1;
    }

    csv_ostream << dyn_format(PRINT_FORMAT, "TAG", "SIZE", "METHOD", "DURATION")
                << "\n";

    for (size_t i = 0; i < test_max_iter; ++i) {
        testString(csv_ostream, test_max_size);
    }

    return 0;
}
