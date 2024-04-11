#ifndef MIPT2024S_3_KOSHELEV_A_TIMER_HPP
#define MIPT2024S_3_KOSHELEV_A_TIMER_HPP

#include <chrono>
#include <iostream>

template <typename ChronoT = std::chrono::nanoseconds>
class Timer {
  private:
    const char* function_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

  public:
    Timer(const char* calling_function)
        : start_time_(std::chrono::high_resolution_clock::now()),
          function_name(calling_function) {}

    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::cout << function_name << " named at " << (void*)function_name << ": "
                  << std::chrono::duration_cast<ChronoT>(end_time - start_time_)
                  << "\n";
    };
};

#endif  // MIPT2024S_3_KOSHELEV_A_TIMER_HPP
