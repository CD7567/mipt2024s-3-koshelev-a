#ifndef STACK_LIB_ABSTRACT_STACK_HXX
#define STACK_LIB_ABSTRACT_STACK_HXX

#include <cstddef>
#include <exception>

namespace stack_lib {

class ExtractFromEmptyStackException final : public std::exception {
  public:
    [[nodiscard]] const char* what() const noexcept override {
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

    [[nodiscard]] virtual bool IsEmpty() const noexcept = 0;

    [[nodiscard]] virtual std::size_t Size() const noexcept = 0;

    [[nodiscard]] virtual T& Top() = 0;

    [[nodiscard]] virtual const T& Top() const = 0;

    virtual void Push(const T& elem) = 0;

    virtual void Push(T&& elem) = 0;

    virtual void Pop() = 0;
};

}  // namespace stack_lib

#endif  // STACK_LIB_ABSTRACT_STACK_HXX
