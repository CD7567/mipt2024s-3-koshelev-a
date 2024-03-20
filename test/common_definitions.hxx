#ifndef TEST_COMMON_DEFINITIONS_HXX
#define TEST_COMMON_DEFINITIONS_HXX

constexpr const char* TEST_JSON_PATH = "./data-test.json";

struct TestStruct {
    size_t number_ = 1000L;
    std::string string_ = "I am string";
};

#endif  // TEST_COMMON_DEFINITIONS_HXX
