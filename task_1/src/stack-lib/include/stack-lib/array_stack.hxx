#ifndef STACK_LIB_ARRAY_STACK_HXX
#define STACK_LIB_ARRAY_STACK_HXX


#include <algorithm>
#include <cstddef>

#include <new>
#include <stack-lib/abstract_stack.hxx>

namespace stack_lib {

    template <typename T>
    class ArrayStack : public AbstractStack<T> {
        private:
        T* buffer_;
        size_t capacity_;
        size_t size_ = 0;

        public:
        /*
            Constructors & destructors
        */

        explicit ArrayStack(size_t capacity = 1) : buffer_(new T[capacity]), capacity_(capacity) {};

        ArrayStack(const ArrayStack<T>& other) : capacity_(other.capacity_), size_(other.size_), buffer_(new T[other.capacity_]) {
            std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
        };

        ArrayStack(ArrayStack<T>&& other) noexcept : capacity_(other.capacity_), size_(other.size_), buffer_(other.buffer_) {
            other.buffer_ = new T[1];
            other.size_ = 0;
            other.capacity_ = 1;
        };

        ~ArrayStack() {
            delete[] buffer_;
        };

        /*
            Operators
        */

        auto& operator=(const ArrayStack<T>& other) {
            if (this != &other) {
                delete[] buffer_;

                buffer_ = new T[other.capacity_];
                std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
                size_ = other.size_;
                capacity_ = other.capacity_;
            }

            return *this;
        };

        auto& operator=(ArrayStack<T>&& other) noexcept {
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

        [[nodiscard]]
        bool empty() const {
            return size_ == 0;
        };

        [[nodiscard]]
        std::size_t size() const {
            return size_;
        };

        [[nodiscard]]
        std::size_t capacity() const {
            return capacity_;
        }

        [[nodiscard]]
        T& top() {
            return buffer_[size_ - 1];
        }

        [[nodiscard]]
        const T& top() const {
            return buffer_[size_ - 1];
        }

        void push(const T& elem) {
            if (size_ == capacity_) {
                T* new_buffer = new T[2 * capacity_];

                std::copy(buffer_, buffer_ + capacity_, new_buffer);
                delete[] buffer_;
                buffer_ = new_buffer;
                capacity_ = 2 * capacity_;
            }

            buffer_[size_++] = elem;
        };
    
        void push(T&& elem) {
            if (size_ == capacity_) {
                T* new_buffer = new T[2 * capacity_];

                std::copy(buffer_, buffer_ + capacity_, new_buffer);
                delete[] buffer_;
                buffer_ = new_buffer;
                capacity_ = 2 * capacity_;
            }

            buffer_[size_++] = elem;
        }

        void pop() {
            if (size_ == 0) {
                throw ExtractFromEmptyStackException();
            }

            --size_;
        };

        void shrink() {
            if (size_ != capacity_ && size_ != 0) {
                T* new_buffer = new T[size_];

                std::copy(buffer_, buffer_ + size_, new_buffer);
                delete[] buffer_;
                buffer_ = new_buffer;
                capacity_ = size_;
            }
        }
    };

} // namespace stack_lib

#endif