#ifndef FULLREAD_PARSER_TEST_HPP
#define FULLREAD_PARSER_TEST_HPP

#include <doctest/doctest.h>

#include <nlohmann/json.hpp>

#include "../common_definitions.hpp"
#include "fullread_parser.hpp"

using json = nlohmann::json;

TEST_SUITE("TestFullreadParser") {
    TEST_CASE("TestReadingCorrectness") {
        json data = json::parse(std::ifstream(TEST_JSON_PATH));
        FullreadParser parser(TEST_JSON_PATH);
        parser.Parse();

        REQUIRE_EQ(parser.GetData().size(), data.size());

        for (size_t i = 0; i < data.size(); ++i) {
            REQUIRE_EQ(parser.GetData()[i].user_.value_,
                       data[i]["user"].get<std::string>());
            REQUIRE_EQ(parser.GetData()[i].question_.value_,
                       data[i]["question"].get<std::string>());
            REQUIRE_EQ(parser.GetData()[i].score_.value_,
                       data[i]["score"].get<int>());
        }
    }
}

#endif  // FULLREAD_PARSER_TEST_HPP
