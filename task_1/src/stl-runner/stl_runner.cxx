#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <list>
#include <stack>

constexpr size_t TEST_STRING_SIZE_LIMIT = 4096L;
constexpr const char* PRINT_FORMAT = "%15s,%10lu,%20s,%10ld\n";
constexpr const char* PRINT_HEADER_FORMAT = "%15s,%10s,%20s,%10s\n";

struct TestStruct {
    size_t number_ = 1000L;
    std::string string_ = "I am string";
};

/** @brief Test STL stack implementations
 * @tparam T Template parameter for stack
 * @tparam C Base STL container for std::stack
 * @param f_out_csv File to store data
 * @param test_max_size Max amount of elements for test
 * @param tag Discriminator for data processing
 * @param elem Element to store in stack
 */
template <typename T, typename C>
void testSTL(FILE* f_out_csv, size_t test_max_size, const char* tag,
             const T& elem) {
    std::stack<T, C> stack;

    for (size_t i = 0; i < test_max_size; ++i) {
        // Measuring push time
        auto start = std::chrono::high_resolution_clock::now();
        stack.push(elem);
        auto end = std::chrono::high_resolution_clock::now();

        (void)fprintf(
            f_out_csv, PRINT_FORMAT, tag, i, "PUSH",
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count());

        // Measuring copy construction time
        start = std::chrono::high_resolution_clock::now();
        std::stack<T, C> copied(stack);
        end = std::chrono::high_resolution_clock::now();

        (void)fprintf(
            f_out_csv, PRINT_FORMAT, tag, i, "COPY_CONSTRUCTOR",
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count());
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        return 1;
    }

    FILE* f_out_csv = fopen("./data/data.csv", "a");
    FILE* f_in_txt = fopen("./data/test_string.txt", "r");

    char* test_string = new char[TEST_STRING_SIZE_LIMIT];

    (void)fgets(test_string, TEST_STRING_SIZE_LIMIT, f_in_txt);
    (void)fclose(f_in_txt);

    if (std::strcmp(argv[3], "true") == 0) {
        (void)fprintf(f_out_csv, PRINT_HEADER_FORMAT, "TAG", "SIZE", "METHOD",
                      "DURATION");
    }

    for (size_t i = 0; i < std::stoul(argv[1]); ++i) {
        testSTL<TestStruct, std::vector<TestStruct>>(
            f_out_csv, std::stoul(argv[2]), "STL_ARRAY",
            TestStruct(1000L, test_string));
        testSTL<TestStruct, std::list<TestStruct>>(
            f_out_csv, std::stoul(argv[2]), "STL_LIST",
            TestStruct(1000L, test_string));
    }

    (void)fclose(f_out_csv);
    delete[] test_string;
}