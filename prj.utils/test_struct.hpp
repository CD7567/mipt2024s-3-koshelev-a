#ifndef MIPT2024S_3_KOSHELEV_A_TEST_STRUCT_HPP
#define MIPT2024S_3_KOSHELEV_A_TEST_STRUCT_HPP

#include <cstddef>
#include <string>

struct TestStruct {
    size_t number_ = 0;
    std::string string_ = "I am string";

    bool operator==(const TestStruct& other) const {
        return number_ == other.number_ && string_ == other.string_;
    }
};

#endif  // MIPT2024S_3_KOSHELEV_A_TEST_STRUCT_HPP
