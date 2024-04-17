#ifndef MIPT2024S_3_KOSHELEV_A_TIMERANCHOR_HPP
#define MIPT2024S_3_KOSHELEV_A_TIMERANCHOR_HPP

#include <unordered_map>

#include "timingunit.hpp"

class TimerAnchor {
  public:
    TimingUnit& node_;

    TimerAnchor(const char* function_name);
};

#endif  // MIPT2024S_3_KOSHELEV_A_TIMERANCHOR_HPP
