#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "sax_event_consumer.hxx"
#include "util-lib/utils.hxx"

using json = nlohmann::json;

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10}";

/**
 * Test nlohmann DOM parser
 * @param out Fstream to store data
 * @param json_path Data json path
 */
inline void testLibraryDOM(std::ofstream& out, const char* json_path) {
    std::ifstream f_json(json_path);

    // Measure parsing time
    size_t parsing_time = timeit<std::chrono::milliseconds>(
        [&f_json]() { const json parsed = json::parse(f_json); });

    out << dyn_format(PRINT_FORMAT, "DOM", parsing_time) << "\n";
}

/**
 * Test nlohmann SAX parser
 * @param out Fstream to store data
 * @param json_path Data json path
 */
inline void testLibrarySAX(std::ofstream& out, const char* json_path) {
    std::ifstream f_json(json_path);
    SAXEventConsumer consumer;

    // Measure parsing time
    size_t parsing_time = timeit<std::chrono::milliseconds>(
        [&f_json, &consumer]() { json::sax_parse(f_json, &consumer); });

    out << dyn_format(PRINT_FORMAT, "SAX", parsing_time) << "\n";
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
        testLibraryDOM(csv_ostream, argv[1]);
        testLibrarySAX(csv_ostream, argv[1]);
    }

    return 0;
}
