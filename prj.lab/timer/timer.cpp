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
    for (auto& entry : map_) {
        std::cout << entry.first << ": " << entry.second.sum_time_ << "/"
                  << entry.second.count_ << "="
                  << entry.second.sum_time_ / entry.second.count_ << "\n";
    }
}
