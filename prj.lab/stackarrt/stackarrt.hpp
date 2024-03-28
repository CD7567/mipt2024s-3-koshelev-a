#ifndef MIPT2024S_3_KOSHELEV_A_STACKARRT_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKARRT_HPP

#include <algorithm>
#include <cstddef>

#include "stackarrtexception.hpp"

template <typename T>
class StackArrT final {
  private:
    T* buffer_;
    size_t capacity_;
    size_t size_ = 0;

  public:
    /*
     * Constructors & destructors
     */

    explicit StackArrT(const size_t capacity = 1)
        : buffer_(new T[capacity]), capacity_(capacity) {}

    StackArrT(const StackArrT& other)
        : buffer_(new T[other.capacity_]),
          capacity_(other.capacity_),
          size_(other.size_) {
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }

    StackArrT(StackArrT&& other) noexcept
        : buffer_(other.buffer_),
          capacity_(other.capacity_),
          size_(other.size_) {
        other.buffer_ = new T[1];
        other.size_ = 0;
        other.capacity_ = 1;
    }

    ~StackArrT() { delete[] buffer_; }

    /*
     * Operators
     */

    auto& operator=(const StackArrT& other) {
        if (this != &other) {
            delete[] buffer_;

            buffer_ = new T[other.capacity_];
            std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
            size_ = other.size_;
            capacity_ = other.capacity_;
        }

        return *this;
    }

    auto& operator=(StackArrT&& other) noexcept {
        if (this != &other) {
            delete[] buffer_;

            buffer_ = other.buffer_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.buffer_ = new T[1];
            other.size_ = 0;
            other.capacity_ = 1;
        }

        return *this;
    }

    /*
     * Member functions
     */

    [[nodiscard]] bool IsEmpty() const noexcept { return size_ == 0; }

    [[nodiscard]] std::size_t Size() const noexcept { return size_; }

    [[nodiscard]] std::size_t Capacity() const noexcept { return capacity_; }

    [[nodiscard]] T& Top() override {
        if (size_ == 0) {
            throw StackArrTException("Cannot extract from empty stack!");
        }

        return buffer_[size_ - 1];
    }

    [[nodiscard]] const T& Top() const {
        if (size_ == 0) {
            throw StackArrTException("Cannot extract from empty stack!");
        }

        return buffer_[size_ - 1];
    }

    void Push(const T& elem) {
        if (size_ == capacity_) {
            T* new_buffer = new T[2 * capacity_];

            for (size_t i = 0; i < capacity_; ++i) {
                new_buffer[i] = T(std::move(buffer_[i]));
            }

            delete[] buffer_;
            buffer_ = new_buffer;
            capacity_ *= 2;
        }

        buffer_[size_++] = elem;
    }

    void Push(T&& elem) {
        if (size_ == capacity_) {
            T* new_buffer = new T[2 * capacity_];

            for (size_t i = 0; i < capacity_; ++i) {
                new_buffer[i] = T(std::move(buffer_[i]));
            }

            delete[] buffer_;
            buffer_ = new_buffer;
            capacity_ *= 2;
        }

        buffer_[size_++] = elem;
    }

    void Pop() {
        if (size_ == 0) {
            throw StackArrTException("Cannot extract from empty stack!");
        }

        --size_;
    }

    void Shrink() {
        if (size_ != capacity_ && size_ != 0) {
            T* new_buffer = new T[size_];

            for (size_t i = 0; i < size_; ++i) {
                new_buffer[i] = T(std::move(buffer_[i]));
            }

            delete[] buffer_;
            buffer_ = new_buffer;
            capacity_ = size_;
        }
    }
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKARRT_HPP
