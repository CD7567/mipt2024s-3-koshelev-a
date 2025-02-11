#ifndef MIPT2024S_3_KOSHELEV_A_UTILS_HPP
#define MIPT2024S_3_KOSHELEV_A_UTILS_HPP

#include <chrono>
#include <cmath>
#include <format>
#include <random>
#include <climits>

#define TIME(funcCall, ChronoType, storage)                                    \
    {                                                                          \
        auto start = std::chrono::high_resolution_clock::now();                \
        funcCall;                                                              \
        auto end = std::chrono::high_resolution_clock::now();                  \
        storage = std::chrono::duration_cast<ChronoType>(end - start).count(); \
    }

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
 * Рассчитать среднее значение выборки
 * @tparam SAMPLE_SIZE Размер выборки
 * @param sample Выборка
 * @return Среднее значение выборки
 */
template <size_t SAMPLE_SIZE>
size_t calculate_mean(std::array<size_t, SAMPLE_SIZE>& sample) {
    double sum = 0;

    for (auto it : sample) {
        sum += it;
    }

    return sum / (double)SAMPLE_SIZE;
}

/**
 * Рассчитать стандартное отклонение выборки
 * @tparam SAMPLE_SIZE Размер выборки
 * @param sample Выборка
 * @return Пара из среднего значения и стандартного отклонения выборки
 */
template <size_t SAMPLE_SIZE>
std::pair<double, double> calculate_deviation(
    std::array<size_t, SAMPLE_SIZE>& sample) {
    double mean = calculate_mean(sample);
    double dev_sum = 0;

    for (auto it : sample) {
        double dev = it - mean;
        dev_sum += dev * dev;
    }

    return std::make_pair(mean, sqrt(dev_sum / (double)SAMPLE_SIZE));
}

/**
 * Генератор случайного символа
 * @return Случайный символ
 */
char genRandomChar() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution;

    return distribution(generator) % CHAR_MAX;
}

#endif  // MIPT2024S_3_KOSHELEV_A_UTILS_HPP
