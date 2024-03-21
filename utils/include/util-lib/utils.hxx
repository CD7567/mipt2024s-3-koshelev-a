#ifndef UTILS_LIB_UTILS_HXX
#define UTILS_LIB_UTILS_HXX

#include <chrono>
#include <format>

/**
 * Dynamically format string
 * @tparam Args Typenames of args
 * @param format_str Format string
 * @param args Format args
 * @return Formatted string
 */
template <typename... Args>
std::string dyn_format(std::string_view format_str, Args&&... args) {
    return std::vformat(format_str, std::make_format_args(args...));
}

/**
 * Time profile given function wrapped in lambda
 * @tparam ChronoT std::chrono result unit type
 * @tparam Lambda Profiled function type
 * @tparam Args Profiled function arguments types
 * @param lambda Profiled function
 * @param args Profiled function arguments
 * @return Time in given units
 */
template <typename ChronoT, typename Lambda, typename... Args>
inline size_t timeit(Lambda&& lambda, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    lambda(args...);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<ChronoT>(end - start).count();
}

#endif  // UTILS_LIB_UTILS_HXX
