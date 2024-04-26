#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "fullread_parser.hpp"
#include "sax_event_consumer.hpp"
#include "stream_parser.hpp"
#include "utils.hpp"

using json = nlohmann::json;

constexpr const char* PRINT_FORMAT = "{0:>15},{1:>10}";

/**
 * Test custom parser
 * @tparam Parser Parser implementation
 * @param out Fstream to store data
 * @param tag Discriminator for data processing
 * @param json_path Path to json file
 */
template <typename Parser>
inline void testCustomParser(std::ofstream& out, std::string tag,
                             const char* json_path) {
    Parser parser(json_path);
    size_t time = 0;

    // Measure parsing time
    TIME(parser.Parse(), std::chrono::nanoseconds, time);

    out << dyn_format(PRINT_FORMAT, tag, time) << "\n";
}

/**
 * Test nlohmann DOM parser
 * @param out Fstream to store data
 * @param json_path Data json path
 */
inline void testLibraryDOM(std::ofstream& out, const char* json_path) {
    std::ifstream f_json(json_path);
    size_t time = 0;

    // Measure parsing time
    TIME(json parsed = json::parse(f_json), std::chrono::nanoseconds, time);    // NOLINT

    out << dyn_format(PRINT_FORMAT, "DOM", time) << "\n";
}

/**
 * Test nlohmann SAX parser
 * @param out Fstream to store data
 * @param json_path Data json path
 */
inline void testLibrarySAX(std::ofstream& out, const char* json_path) {
    std::ifstream f_json(json_path);
    SAXEventConsumer consumer;
    size_t time = 0;

    // Measure parsing time
    TIME(json::sax_parse(f_json, &consumer), std::chrono::nanoseconds, time);

    out << dyn_format(PRINT_FORMAT, "SAX", time) << "\n";
}

/**
 * Main function of runner
 * @param argc Number of command line arguments
 * @param argv[1] Path to json file for data output
 * @param argv[2] Path to file for data output
 * @param argv[3] Amount of iterations
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

    std::ofstream csv_ostream(argv[2], std::ios_base::app);

    const size_t test_max_iter = std::stoul(argv[3]);

    if (!csv_ostream.good()) {
        std::cerr << "Couldn't open files!"
                  << "\n";
        return 1;
    }

    csv_ostream << dyn_format(PRINT_FORMAT, "TAG", "DURATION") << "\n";

    for (size_t i = 0; i < test_max_iter; ++i) {
        testCustomParser<StreamParser>(csv_ostream, "STREAM", argv[1]);
        testCustomParser<FullreadParser>(csv_ostream, "FULLREAD", argv[1]);
        testLibraryDOM(csv_ostream, argv[1]);
        testLibrarySAX(csv_ostream, argv[1]);
    }

    return 0;
}
