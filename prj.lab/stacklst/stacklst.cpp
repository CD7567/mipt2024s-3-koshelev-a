#include "stacklst.hpp"

StackLst::StackLst(const StackLst& other) : size_(other.size_) {
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

StackLst::StackLst(StackLst&& other) noexcept
    : top_(other.top_), size_(other.size_) {
    other.size_ = 0;
    other.top_ = nullptr;
}

StackLst::~StackLst() {
    while (top_ != nullptr) {
        Node* tmp = top_;
        top_ = top_->prev_;

        delete tmp;
    }
}

auto& StackLst::operator=(const StackLst& other) {
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

auto& StackLst::operator=(StackLst&& other) noexcept {
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

bool StackLst::IsEmpty() const noexcept { return size_ == 0; }

std::size_t StackLst::Size() const noexcept { return size_; }

float& StackLst::Top() {
    if (size_ == 0) {
        throw StackLstException("Cannot extract from empty stack!");
    }

    return top_->elem_;
}

const float& StackLst::Top() const {
    if (size_ == 0) {
        throw StackLstException("Cannot extract from empty stack!");
    }

    return top_->elem_;
}

void StackLst::Push(const float& elem) {
    top_ = new Node{elem, top_};
    ++size_;
}

void StackLst::Pop() {
    if (size_ == 0) {
        throw StackLstException("Cannot extract from empty stack!");
    }

    Node* tmp = top_;

    top_ = top_->prev_;
    --size_;

    delete tmp;
}
