#ifndef MIPT2024S_3_KOSHELEV_A_TIMER_HPP
#define MIPT2024S_3_KOSHELEV_A_TIMER_HPP

#include <chrono>
#include <iostream>
#include <unordered_map>

#include "timeranchor.hpp"
#include "timingunit.hpp"

#ifdef DO_ON_TIME
#define PUT_ON_TIME(funcName)                                                  \
    static auto anchor = TimerAnchor(funcName);                                \
    Timer timer(anchor);
#else
#define PUT_ON_TIME(funcName)
#endif

class Timer {
  private:
    TimerAnchor& anchor_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;

  public:
    inline static auto map_ = std::unordered_map<const char*, TimingUnit>();

    Timer(TimerAnchor& anchor);

    ~Timer();

    static void print();
};

#endif  // MIPT2024S_3_KOSHELEV_A_TIMER_HPP
