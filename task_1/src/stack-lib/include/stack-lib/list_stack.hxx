#ifndef STACK_LIB_LIST_STACK_HXX
#define STACK_LIB_LIST_STACK_HXX


#include <cstddef>

#include <stack-lib/abstract_stack.hxx>


namespace stack_lib {

    template <typename T>
    struct Node {
        T elem_;
        Node<T>* prev_;
    };

    template <typename T>
    class ListStack : public AbstractStack<T>{
        private:
        Node<T>* top_ = nullptr;
        size_t size_ = 0;

        public:
        /*
            Constructors & destructors
        */

        ListStack() = default;

        ListStack(const ListStack& other) : size_(other.size_) {
            if (other.top_ != nullptr) {
                Node<T>* other_it = other.top_;
                Node<T>* this_it = nullptr;

                this_it = top_ = new Node<T>{other.top_->elem_, nullptr};

                while (other_it->prev_ != nullptr) {
                    this_it->prev_ = new Node<T>{other.top_->prev_->elem_, nullptr};
                    other_it = other_it->prev_;
                    this_it = this_it->prev_;
                }
            }
        }

        ListStack(ListStack&& other) noexcept : top_(other.top_), size_(other.size_) {
            other.size_ = 0;
            other.top_ = nullptr;
        }

        ~ListStack() override {
            Node<T>* tmp = nullptr;

            while (top_ != nullptr) {
                tmp = top_;
                top_ = top_->prev_;
            
                delete tmp;
            }
        }

        /*
            Operators
        */

        auto& operator=(const ListStack<T>& other) {
            if (this != &other && other.top_ != nullptr) {
                Node<T>* other_it = other.top_;
                Node<T>* this_it = nullptr;

                this_it = top_ = new Node<T>{other.top_->elem_, nullptr};

                while (other_it->prev_ != nullptr) {
                    this_it->prev_ = new Node<T>{other.top_->prev_->elem_, nullptr};
                    other_it = other_it->prev_;
                    this_it = this_it->prev_;
                }
            }
            
            size_ = other.size_;

            return *this;
        }

        auto& operator=(ListStack<T>&& other) noexcept {
            Node<T>* tmp = nullptr;

            while (top_ != nullptr) {
                tmp = top_;
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
            Member functions
        */

        [[nodiscard]]
        bool empty() const override {
            return size_ == 0;
        }

        [[nodiscard]]
        std::size_t size() const override {
            return size_;
        }

        [[nodiscard]]
        T& top() override {
            if (size_ == 0) {
                throw ExtractFromEmptyStackException();
            }

            return top_->elem_;
        }

        [[nodiscard]]
        const T& top() const override {
            if (size_ == 0) {
                throw ExtractFromEmptyStackException();
            }

            return top_->elem_;
        }

        void push(const T& elem) override {
            top_ = new Node<T>{elem, top_};
            ++size_;
        }
    
        void push(T&& elem) override {
            top_ = new Node<T>{elem, top_};
            ++size_;
        }

        void pop() override {
            if (size_ == 0) {
                throw ExtractFromEmptyStackException();
            }

            Node<T>* tmp = top_;

            top_ = top_->prev_;
            --size_;

            delete tmp; 
        }
    };

} // namespace stack_lib

#endif