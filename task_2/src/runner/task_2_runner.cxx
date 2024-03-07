#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

constexpr const char* PRINT_FORMAT = "%15s,%10lu,%20s,%10ld\n";
constexpr const char* PRINT_HEADER_FORMAT = "%15s,%10s,%20s,%10s\n";

inline void testLibrary(FILE* f_out_csv, const char* json_path) {
    std::ifstream f_json("task_2/data/data-medium.json");

    // Measuring parsing time
    auto start = std::chrono::high_resolution_clock::now();
    json data = json::parse(json_path);
    auto end = std::chrono::high_resolution_clock::now();

}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Wrong number of arguments!" << std::endl;
    }

    std::ifstream json_file("task_2/data/data-medium.json");
    json data = json::parse(json_file);

    // std::cout << data.at(0) << std::endl;
}