#ifndef TEST_COMMON_DEFINITIONS_HPP
#define TEST_COMMON_DEFINITIONS_HPP

#include "random"
#include "test_struct.hpp"

#define TEST_SIZE 10
#define TEST_JSON_PATH "data/data-parser-test.json"

/**
 * Генератор случайного целого числа
 * @tparam T Тип числа
 * @return Случайное целое число
 */
template <typename T>
inline T genRandomInt() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<T> distribution(0);

    return distribution(generator);
}

/**
 * Генератор случайного действительного числа
 * @tparam T Типа числа
 * @return Случайное действительное число
 */
template <typename T>
inline T genRandomReal() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_real_distribution<T> distribution(0);

    return distribution(generator);
}

/**
 * Генератор случайной строки строчной латиницей
 * @param size Длина строки
 * @return Случайная строка
 */
inline std::string genRandomString(size_t size = TEST_SIZE) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<char> distribution(97, 122);
    std::string result;

    for (size_t i = 0; i < size; ++i) {
        result += distribution(generator);
    }

    return result;
}

/**
 * Сгенерировать набор тестовых данных
 * @tparam T Тип данных
 * @return Массив данных
 */
template <typename T>
std::array<T, TEST_SIZE> genData();

/**
 * Сгенерировать набор float
 * @return Массив float
 */
template <>
std::array<float, TEST_SIZE> genData<float>() {
    std::array<float, TEST_SIZE> array;

    for (size_t i = 0; i < TEST_SIZE; ++i) {
        array[i] = genRandomReal<float>();
    }

    return array;
}

/**
 * Сгенерировать набор TestStruct
 * @return Массив TestStruct
 */
template <>
std::array<TestStruct, TEST_SIZE> genData<TestStruct>() {
    std::array<TestStruct, TEST_SIZE> array;

    for (size_t i = 0; i < TEST_SIZE; ++i) {
        array[i].number_ = genRandomInt<size_t>();
        array[i].string_ = genRandomString();
    }

    return array;
}

#endif  // TEST_COMMON_DEFINITIONS_HPP
