#ifndef MIPT2024S_3_KOSHELEV_A_STACKLST_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKLST_HPP

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

    [[nodiscard]] bool IsEmpty() const noexcept { return size_ == 0; }

    [[nodiscard]] std::size_t Size() const noexcept { return size_; }

    [[nodiscard]] T& Top() {
        if (size_ == 0) {
            throw StackLstTException("Cannot extract from empty stack!");
        }

        return top_->elem_;
    }

    [[nodiscard]] const T& Top() const {
        if (size_ == 0) {
            throw StackLstTException("Cannot extract from empty stack!");
        }

        return top_->elem_;
    }

    void Push(const T& elem) {
        top_ = new Node{elem, top_};
        ++size_;
    }

    void Push(T&& elem) {
        top_ = new Node{elem, top_};
        ++size_;
    }

    void Pop() {
        if (size_ == 0) {
            throw StackLstTException("Cannot extract from empty stack!");
        }

        Node* tmp = top_;

        top_ = top_->prev_;
        --size_;

        delete tmp;
    }
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKLST_HPP
