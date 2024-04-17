#include "timeranchor.hpp"

#include "timer.hpp"

TimerAnchor::TimerAnchor(const char* function_name)
    : node_(Timer::map_[function_name]) {}
