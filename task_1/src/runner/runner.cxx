#include <bits/chrono.h>
#include <chrono>
#include <concepts>
#include <ctime>
#include <cstddef>
#include <cstdio>
#include <string>
#include <thread>

#include "stack-lib/abstract_stack.hxx"
#include "stack-lib/list_stack.hxx"
#include "stack-lib/array_stack.hxx"

const size_t TEST_STRING_SIZE_LIMIT = 4096;

template <typename T>
concept Derived = std::derived_from<T, stack_lib::AbstractStack<std::string>>;

template<Derived Stack>
void testStack(
    Stack& stack,
    FILE* f_out_csv,
    const char* tag,
    const char* test_string,
    size_t test_max_size
) {
    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        auto start = std::chrono::high_resolution_clock::now();
        stack.push(test_string);
        auto end = std::chrono::high_resolution_clock::now();

        (void)fprintf(
            f_out_csv,
            "%5s,%10lu,%20s,%10ld\n",
            tag,
            i,
            "PUSH",
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
        );

        // Measuring copy construction time
        start = std::chrono::high_resolution_clock::now();
        Stack copied(stack);
        end = std::chrono::high_resolution_clock::now();

        (void)fprintf(
            f_out_csv,
            "%5s,%10lu,%20s,%10ld\n",
            tag,
            i,
            "COPY_CONSTRUCTOR",
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
        );
    }
}

int main(int, char** argv) {
    FILE* f_out_csv = fopen("./data/data.csv", "w");
    FILE* f_in_txt = fopen("./data/test_string.txt", "r");

    char* test_string = new char[TEST_STRING_SIZE_LIMIT];

    (void)fgets(test_string, TEST_STRING_SIZE_LIMIT, f_in_txt);
    (void)fclose(f_in_txt);

    (void)fprintf(
        f_out_csv,
        "%5s,%10s,%20s,%10s\n",
        "TAG",
        "SIZE",
        "METHOD",
        "DURATION"
    );

    for (size_t i = 0; i < std::stoul(argv[1]); ++i) {
        stack_lib::ArrayStack<std::string> array_stack;
        stack_lib::ListStack<std::string> list_stack;
        testStack(array_stack, f_out_csv, "ARRAY", test_string, std::stoul(argv[2]));
        testStack(list_stack, f_out_csv, "LIST", test_string, std::stoul(argv[2]));
    }

    (void)fclose(f_out_csv);
    delete[] test_string;
}