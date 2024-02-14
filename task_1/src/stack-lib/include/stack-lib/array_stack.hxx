#ifndef STACK_LIB_ARRAY_STACK_HXX
#define STACK_LIB_ARRAY_STACK_HXX

#include <algorithm>

#include "stack-lib/abstract_stack.hxx"

namespace stack_lib {

template <typename T>
class ArrayStack final : public AbstractStack<T> {
  private:
    T* buffer_;
    size_t capacity_;
    size_t size_ = 0;

  public:
    /*
        Constructors & destructors
    */

    explicit ArrayStack(const size_t capacity = 1)
        : buffer_(new T[capacity]), capacity_(capacity) {}

    ArrayStack(const ArrayStack& other)
        : buffer_(new T[other.capacity_]),
          capacity_(other.capacity_),
          size_(other.size_) {
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }

    ArrayStack(ArrayStack&& other) noexcept
        : buffer_(other.buffer_),
          capacity_(other.capacity_),
          size_(other.size_) {
        other.buffer_ = new T[1];
        other.size_ = 0;
        other.capacity_ = 1;
    }

    ~ArrayStack() override { delete[] buffer_; }

    /*
        Operators
    */

    auto& operator=(const ArrayStack& other) {
        if (this != &other) {
            delete[] buffer_;

            buffer_ = new T[other.capacity_];
            std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
            size_ = other.size_;
            capacity_ = other.capacity_;
        }

        return *this;
    }

    auto& operator=(ArrayStack&& other) noexcept {
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
        Member functions
    */

    [[nodiscard]] bool IsEmpty() const noexcept override { return size_ == 0; }

    [[nodiscard]] std::size_t Size() const noexcept override { return size_; }

    [[nodiscard]] std::size_t Capacity() const noexcept { return capacity_; }

    [[nodiscard]] T& Top() override {
        if (size_ == 0) {
            throw ExtractFromEmptyStackException();
        }

        return buffer_[size_ - 1];
    }

    [[nodiscard]] const T& Top() const override {
        if (size_ == 0) {
            throw ExtractFromEmptyStackException();
        }

        return buffer_[size_ - 1];
    }

    void Push(const T& elem) override {
        if (size_ == capacity_) {
            T* new_buffer = new T[2 * capacity_];

            std::copy(buffer_, buffer_ + capacity_, new_buffer);
            delete[] buffer_;
            buffer_ = new_buffer;
            capacity_ *= 2;
        }

        buffer_[size_++] = elem;
    }

    void Push(T&& elem) override {
        if (size_ == capacity_) {
            T* new_buffer = new T[2 * capacity_];

            std::copy(buffer_, buffer_ + capacity_, new_buffer);
            delete[] buffer_;
            buffer_ = new_buffer;
            capacity_ *= 2;
        }

        buffer_[size_++] = elem;
    }

    void Pop() override {
        if (size_ == 0) {
            throw ExtractFromEmptyStackException();
        }

        --size_;
    }

    void Shrink() {
        if (size_ != capacity_ && size_ != 0) {
            T* new_buffer = new T[size_];

            std::copy(buffer_, buffer_ + size_, new_buffer);
            delete[] buffer_;
            buffer_ = new_buffer;
            capacity_ = size_;
        }
    }
};

}  // namespace stack_lib

#endif