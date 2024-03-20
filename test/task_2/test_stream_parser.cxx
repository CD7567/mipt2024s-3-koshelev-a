#include <doctest/doctest.h>
#include <nlohmann/json.hpp>

#include "../common_definitions.hxx"
#include "json-lib/stream_parser.hxx"

using json = nlohmann::json;

TEST_SUITE("TestStreamParser") {
    TEST_CASE("TestReadingCorrectness") {
        json data = json::parse(std::ifstream(TEST_JSON_PATH));
        json_lib::StreamParser parser(TEST_JSON_PATH);
        parser.Parse();

        REQUIRE_EQ(parser.GetData().size(), data.size());
    }
}