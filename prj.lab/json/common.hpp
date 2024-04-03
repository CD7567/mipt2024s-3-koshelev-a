#ifndef JSON_LIB_COMMON_HXX
#define JSON_LIB_COMMON_HXX

#include <string>

constexpr size_t USER_LABEL_LENGTH = 4;
constexpr size_t QUESTION_LABEL_LENGTH = 8;
constexpr size_t SCORE_LABEL_LENGTH = 5;

constexpr size_t USER_VALUE_LENGTH = 36;
constexpr size_t QUESTION_VALUE_LENGTH = 36;
constexpr size_t SCORE_VALUE_LENGTH = 1;

template <typename T>
struct JSONEntry {
    std::string key_;
    T value_;
};

struct JSONBlock {
    JSONEntry<std::string> user_;
    JSONEntry<std::string> question_;
    JSONEntry<int> score_;
};

#endif  // JSON_LIB_COMMON_HXX
