#ifndef STACK_LIB_ABSTRACT_STACK_HXX
#define STACK_LIB_ABSTRACT_STACK_HXX


#include <cstddef>
#include <exception>


namespace stack_lib {
    class ExtractFromEmptyStackException : public std::exception {
        public:
        [[nodiscard]]
        const char* what() const noexcept override {
            return "Cannot extract value from empty stack";
        }
    };


    template <typename T>
    class AbstractStack {
        public:
        /*
            Constructors & destructors
        */

        AbstractStack() = default;

        AbstractStack(const AbstractStack<T>& other) = delete;

        AbstractStack(AbstractStack<T>&& other) = delete;

        virtual ~AbstractStack() = default;

        /*
            Operators
        */

        auto& operator=(const AbstractStack<T>& other) = delete;

        auto& operator=(AbstractStack<T>&& other) noexcept = delete;

        /*
            Member functions
        */

        [[nodiscard]]
        virtual bool empty() const = 0;

        [[nodiscard]]
        virtual std::size_t size() const = 0;

        [[nodiscard]]
        virtual T& top() = 0;

        [[nodiscard]]
        virtual const T& top() const = 0;

        virtual void push(const T& elem) = 0;
    
        virtual void push(T&& elem) = 0;

        virtual void pop() = 0;
    };

} // namespace stack_lib

#endif