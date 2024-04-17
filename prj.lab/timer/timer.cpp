#include "timer.hpp"

Timer::Timer(TimerAnchor& anchor)
    : anchor_(anchor), start_time_(std::chrono::high_resolution_clock::now()) {}

Timer::~Timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    ++anchor_.node_.count_;
    anchor_.node_.sum_time_ +=
        std::chrono::duration_cast<std::chrono::nanoseconds>(end_time -
                                                             start_time_)
            .count();
}

void Timer::print() {
    for (auto& it : map_) {
        std::cout << it.first << ": " << it.second.sum_time_ << "/" << it.second.count_ << "=" << it.second.sum_time_ / it.second.count_ << "\n";
    }
}
