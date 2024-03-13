#include <fstream>
#include <iostream>
#include <chrono>
#include <nlohmann/json.hpp>

#include "json-lib/stream_parser.hxx"

using json = nlohmann::json;

constexpr const char* PRINT_FORMAT = "%15s,%10lu,%20s,%10ld\n";
constexpr const char* PRINT_HEADER_FORMAT = "%15s,%10s,%20s,%10s\n";

class SAXEventConsumer : public json::json_sax_t {
  public:
    std::vector<std::string> events;

    bool null() override {
        events.emplace_back("null()");
        return true;
    }

    bool boolean(bool val) override {
        events.push_back("boolean(val=" + std::string(val ? "true" : "false") +
                         ")");
        return true;
    }

    bool number_integer(number_integer_t val) override {
        events.push_back("number_integer(val=" + std::to_string(val) + ")");
        return true;
    }

    bool number_unsigned(number_unsigned_t val) override {
        events.push_back("number_unsigned(val=" + std::to_string(val) + ")");
        return true;
    }

    bool number_float(number_float_t val, const string_t& s) override {
        events.push_back("number_float(val=" + std::to_string(val) +
                         ", s=" + s + ")");
        return true;
    }

    bool string(string_t& val) override {
        events.push_back("string(val=" + val + ")");
        return true;
    }

    bool start_object(std::size_t elements) override {
        events.push_back("start_object(elements=" + std::to_string(elements) +
                         ")");
        return true;
    }

    bool end_object() override {
        events.emplace_back("end_object()");
        return true;
    }

    bool start_array(std::size_t elements) override {
        events.push_back("start_array(elements=" + std::to_string(elements) +
                         ")");
        return true;
    }

    bool end_array() override {
        events.emplace_back("end_array()");
        return true;
    }

    bool key(string_t& val) override {
        events.push_back("key(val=" + val + ")");
        return true;
    }

    bool binary(json::binary_t& val) {
        events.emplace_back("binary(val=[...])");
        return true;
    }

    bool parse_error(std::size_t position, const std::string& last_token,
                     const json::exception& ex) override {
        events.push_back("parse_error(position=" + std::to_string(position) +
                         ", last_token=" + last_token +
                         ",\n            ex=" + std::string(ex.what()) + ")");
        return false;
    }
};

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

int main(int argc, char** argv) {
    if (argc < 0) {
        std::cerr << "Wrong number of arguments!" << std::endl;
    }

    testLibraryDOM(nullptr, "task_2/data/data-medium.json");
    testLibrarySAX(nullptr, "task_2/data/data-medium.json");
    testCustomStream(nullptr, "task_2/data/data-medium.json");
}