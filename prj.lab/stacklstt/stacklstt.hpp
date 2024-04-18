#ifndef MIPT2024S_3_KOSHELEV_A_STACKLSTT_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKLSTT_HPP

#include <cstddef>

#include "stacklsttexception.hpp"

template <typename T>
class StackLstT final {
  private:
    struct Node {
        T elem_;
        Node* prev_;
    };

    Node* top_ = nullptr;
    size_t size_ = 0;

  public:
    /*
     * Constructors & destructors
     */

    StackLstT() = default;

    StackLstT(const StackLstT& other) : size_(other.size_) {
        PUT_ON_TIME("StackLstT_COPY_CONSTR")

        if (other.top_ != nullptr) {
            Node* other_it = other.top_;
            auto* this_it = new Node{other_it->elem_, nullptr};

            top_ = this_it;

            while (other_it->prev_ != nullptr) {
                this_it->prev_ = new Node{other_it->prev_->elem_, nullptr};
                other_it = other_it->prev_;
                this_it = this_it->prev_;
            }
        }
    }

    StackLstT(StackLstT&& other) noexcept
        : top_(other.top_), size_(other.size_) {
        PUT_ON_TIME("StackLstT_MOVE_CONSTR")

        other.size_ = 0;
        other.top_ = nullptr;
    }

    ~StackLstT() {
        while (top_ != nullptr) {
            Node* tmp = top_;
            top_ = top_->prev_;

            delete tmp;
        }
    }

    /*
     * Operators
     */

    auto& operator=(const StackLstT& other) {
        PUT_ON_TIME("StackLstT_COPY_ASSIGN")

        while (top_ != nullptr) {
            Node* tmp = top_;
            top_ = top_->prev_;

            delete tmp;
        }

        if (this != &other && other.top_ != nullptr) {
            Node* other_it = other.top_;
            auto* this_it = new Node{other_it->elem_, nullptr};

            top_ = this_it;

            while (other_it->prev_ != nullptr) {
                this_it->prev_ = new Node{other_it->prev_->elem_, nullptr};
                other_it = other_it->prev_;
                this_it = this_it->prev_;
            }
        }

        size_ = other.size_;

        return *this;
    }

    auto& operator=(StackLstT&& other) noexcept {
        PUT_ON_TIME("StackLstT_MOVE_ASSIGN")

        while (top_ != nullptr) {
            Node* tmp = top_;
            top_ = top_->prev_;

            delete tmp;
        }

        size_ = other.size_;
        top_ = other.top_;
        other.size_ = 0;
        other.top_ = nullptr;

        return *this;
    }

    /*
     * Member functions
     */

    [[nodiscard]] bool IsEmpty() const noexcept {
        PUT_ON_TIME("StackLstT_IS_EMPTY")
        return size_ == 0;
    }

    [[nodiscard]] std::size_t Size() const noexcept {
        PUT_ON_TIME("StackLstT_SIZE")
        return size_;
    }

    [[nodiscard]] T& Top() {
        PUT_ON_TIME("StackLstT_TOP")

        if (size_ == 0) {
            throw StackLstTException("Cannot extract from empty stack!");
        }

        return top_->elem_;
    }

    [[nodiscard]] const T& Top() const {
        PUT_ON_TIME("StackLstT_TOP_CONST")

        if (size_ == 0) {
            throw StackLstTException("Cannot extract from empty stack!");
        }

        return top_->elem_;
    }

    void Push(const T& elem) {
        PUT_ON_TIME("StackLstT_PUSH")

        top_ = new Node{elem, top_};
        ++size_;
    }

    void Push(T&& elem) {
        PUT_ON_TIME("StackLstT_PUSH_MOVE")

        top_ = new Node{elem, top_};
        ++size_;
    }

    void Pop() {
        PUT_ON_TIME("StackLstT_POP")

        if (size_ == 0) {
            throw StackLstTException("Cannot extract from empty stack!");
        }

        Node* tmp = top_;

        top_ = top_->prev_;
        --size_;

        delete tmp;
    }
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKLSTT_HPP
