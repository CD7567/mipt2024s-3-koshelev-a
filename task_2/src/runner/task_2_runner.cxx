#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "json-lib/fullread_parser.hxx"
#include "json-lib/stream_parser.hxx"
#include "sax_event_consumer.hxx"

using json = nlohmann::json;

constexpr const char* PRINT_FORMAT = "%15s,%10lu,%20s,%10ld\n";
constexpr const char* PRINT_H_FORMAT = "%15s,%10s,%20s,%10s\n";

inline void testLibraryDOM(FILE* f_out_csv, const char* json_path) {
    std::ifstream f_json(json_path);

    // Measuring parsing time
    auto start = std::chrono::high_resolution_clock::now();
    json data = json::parse(f_json);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << std::endl;
}

inline void testLibrarySAX(FILE* f_out_csv, const char* json_path) {
    std::ifstream f_json(json_path);
    SAXEventConsumer consumer;

    // Measuring parsing time
    auto start = std::chrono::high_resolution_clock::now();
    json::sax_parse(f_json, &consumer);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << std::endl;
}

inline void testCustomStream(FILE* f_out_csv, const char* json_path) {
    json_lib::StreamParser parser(json_path);

    // Measuring parsing time
    auto start = std::chrono::high_resolution_clock::now();
    parser.Parse();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << std::endl;
}

inline void testCustomFullread(FILE* f_out_csv, const char* json_path) {
    json_lib::FullreadParser parser(json_path);

    // Measuring parsing time
    auto start = std::chrono::high_resolution_clock::now();
    parser.Parse();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 0) {
        std::cerr << "Wrong number of arguments!" << std::endl;
    }

    testLibraryDOM(nullptr, "task_2/data/data-medium.json");
    testLibrarySAX(nullptr, "task_2/data/data-medium.json");
    testCustomStream(nullptr, "task_2/data/data-medium.json");
    testCustomFullread(nullptr, "task_2/data/data-medium.json");
}