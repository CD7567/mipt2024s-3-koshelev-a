#include "stackarr.hpp"

StackArr::StackArr(size_t capacity)
    : buffer_(new float[capacity]), capacity_(capacity) {}

StackArr::StackArr(const StackArr& other)
    : buffer_(new float[other.capacity_]),
      capacity_(other.capacity_),
      size_(other.size_) {
    std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
}

StackArr::StackArr(StackArr&& other) noexcept
    : buffer_(other.buffer_), capacity_(other.capacity_), size_(other.size_) {
    other.buffer_ = new float[1];
    other.size_ = 0;
    other.capacity_ = 1;
}

StackArr::~StackArr() { delete[] buffer_; }

StackArr& StackArr::operator=(const StackArr& other) {
    if (this != &other) {
        delete[] buffer_;

        buffer_ = new float[other.capacity_];
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    return *this;
}

StackArr& StackArr::operator=(StackArr&& other) noexcept {
    if (this != &other) {
        delete[] buffer_;

        buffer_ = other.buffer_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.buffer_ = new float[1];
        other.size_ = 0;
        other.capacity_ = 1;
    }

    return *this;
}

bool StackArr::IsEmpty() const noexcept { return size_ == 0; }

std::size_t StackArr::Size() const noexcept { return size_; }

std::size_t StackArr::Capacity() const noexcept { return capacity_; }

float& StackArr::Top() {
    if (size_ == 0) {
        throw StackArrException("Cannot extract from empty stack!");
    }

    return buffer_[size_ - 1];
}

const float& StackArr::Top() const {
    if (size_ == 0) {
        throw StackArrException("Cannot extract from empty stack!");
    }

    return buffer_[size_ - 1];
}

void StackArr::Push(const float& elem) {
    if (size_ == capacity_) {
        auto* new_buffer = new float[2 * capacity_];

        for (size_t i = 0; i < capacity_; ++i) {
            new_buffer[i] = buffer_[i];
        }

        delete[] buffer_;
        buffer_ = new_buffer;
        capacity_ *= 2;
    }

    buffer_[size_++] = elem;
}

void StackArr::Pop() {
    if (size_ == 0) {
        throw StackArrException("Cannot extract from empty stack!");
    }

    --size_;
}

void StackArr::Shrink() {
    if (size_ != capacity_ && size_ != 0) {
        auto* new_buffer = new float[size_];

        for (size_t i = 0; i < size_; ++i) {
            new_buffer[i] = buffer_[i];
        }

        delete[] buffer_;
        buffer_ = new_buffer;
        capacity_ = size_;
    }
}
