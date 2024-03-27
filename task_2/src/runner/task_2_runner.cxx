#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "json-lib/fullread_parser.hxx"
#include "json-lib/stream_parser.hxx"
#include "util-lib//utils.hxx"

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10}";

template <typename Parser>
inline void testCustomParser(std::ofstream& out, std::string tag,
                             const char* json_path) {
    Parser parser(json_path);

    // Measure parsing time
    size_t parsing_time =
        timeit<std::chrono::milliseconds>([&parser]() { parser.Parse(); });

    out << dyn_format(PRINT_FORMAT, tag, parsing_time) << "\n";
}

/**
 * Main function of runner
 * @param argc Number of command line arguments
 * @param argv[1] Path to json file for data output
 * @param argv[2] Path to file for data output
 * @param argv[3] Boolean whether to print header
 * @param argv[4] Amount of iterations
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

    std::ofstream csv_ostream(argv[2], std::ios_base::app);

    const size_t test_max_iter = std::stoul(argv[4]);

    if (!csv_ostream.good()) {
        std::cerr << "Couldn't open files!"
                  << "\n";
        return 1;
    }

    if (std::strcmp(argv[3], "true") == 0) {
        csv_ostream << dyn_format(PRINT_FORMAT, "TAG", "DURATION") << "\n";
    }

    for (size_t i = 0; i < test_max_iter; ++i) {
        testCustomParser<json_lib::StreamParser>(csv_ostream, "STREAM",
                                                 argv[1]);
        testCustomParser<json_lib::FullreadParser>(csv_ostream, "FULLREAD",
                                                   argv[1]);
    }

    return 0;
}
