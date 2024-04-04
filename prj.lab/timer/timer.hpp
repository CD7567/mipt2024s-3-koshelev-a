#ifndef MIPT2024S_3_KOSHELEV_A_TIMER_HPP
#define MIPT2024S_3_KOSHELEV_A_TIMER_HPP

#include <chrono>
#include <iostream>

template <typename ChronoT>
class Timer {
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

  public:
    Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<ChronoT>(end_time - start_time_)
                  << "\n";
    };
};

#endif  // MIPT2024S_3_KOSHELEV_A_TIMER_HPP
