#ifndef MIPT2024S_3_KOSHELEV_A_MOVETESTER_HPP
#define MIPT2024S_3_KOSHELEV_A_MOVETESTER_HPP

#include <algorithm>
#include <cstddef>

#include "test_struct.hpp"

template <bool is_correct>
class MoveTester {
  private:
    size_t size_;
    TestStruct* buffer_;

  public:
    MoveTester(size_t size = 128) : size_(size), buffer_(new TestStruct[size]) {}

    MoveTester(const MoveTester& other)
        : size_(other.size_), buffer_(new TestStruct[size_]) {
        std::copy(other.buffer_, other.buffer_ + size_, buffer_);
    }

    MoveTester(MoveTester&& other) : size_(other.size_) {
        if (is_correct) {
            buffer_ = other.buffer_;
            other.size_ = 0;
            other.buffer_ = nullptr;
        } else {
            buffer_ = new TestStruct[size_];
            std::copy(other.buffer_, other.buffer_ + size_, buffer_);
        }
    }

    ~MoveTester() { delete[] buffer_; }

    MoveTester& operator=(const MoveTester& other) {
        if (&other != this) {
            size_ = other.size_;

            delete[] buffer_;
            buffer_ = new TestStruct[size_];
            std::copy(other.buffer_, other.buffer_ + size_, buffer_);
        }

        return *this;
    }

    MoveTester& operator=(MoveTester&& other) {
        if (&other != this) {
            size_ = other.size_;
            delete[] buffer_;

            if (is_correct) {
                buffer_ = other.buffer_;
                other.size_ = 0;
                other.buffer_ = nullptr;
            } else {
                buffer_ = new TestStruct[size_];
                std::copy(other.buffer_, other.buffer_ + size_, buffer_);
            }
        }

        return *this;
    }
};

#endif  // MIPT2024S_3_KOSHELEV_A_MOVETESTER_HPP
