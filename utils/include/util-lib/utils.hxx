#ifndef UTILS_LIB_UTILS_HXX
#define UTILS_LIB_UTILS_HXX

#include <cstddef>
#include <string>

struct TestStruct {
    size_t number_ = 0;
    std::string string_ = "I am string";
};

/**
 * Dynamically format string
 * @tparam Args Typenames of args
 * @param format_str Format string
 * @param args Format args
 * @return Formatted string
 */
template<typename... Args>
std::string dyn_format(std::string_view format_str, Args&&... args)
{
    return std::vformat(format_str, std::make_format_args(args...));
}

#endif  // UTILS_LIB_UTILS_HXX
