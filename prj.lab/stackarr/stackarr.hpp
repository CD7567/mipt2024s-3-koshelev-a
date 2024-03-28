#ifndef MIPT2024S_3_KOSHELEV_A_STACKARRT_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKARRT_HPP

#include <algorithm>
#include <cstddef>

#include "stackarrexception.hpp"

class StackArr final {
  private:
    float* buffer_;
    size_t capacity_;
    size_t size_ = 0;

  public:
    /*
     * Constructors & destructors
     */

    explicit StackArr(size_t capacity = 1);

    StackArr(const StackArr& other);

    StackArr(StackArr&& other) noexcept;

    ~StackArr();

    /*
     * Operators
     */

    auto& operator=(const StackArr& other);

    auto& operator=(StackArr&& other) noexcept;

    /*
     * Member functions
     */

    [[nodiscard]] bool IsEmpty() const noexcept;

    [[nodiscard]] std::size_t Size() const noexcept;

    [[nodiscard]] std::size_t Capacity() const noexcept;

    [[nodiscard]] float& Top();

    [[nodiscard]] const float& Top() const;

    void Push(const float& elem);

    void Pop();

    void Shrink();
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKARRT_HPP
